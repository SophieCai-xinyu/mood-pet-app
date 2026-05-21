#include "DataManager.h"

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>
#include <QTextStream>
#include <algorithm>

DataManager::DataManager(QObject *parent)
    : QObject(parent)
{
    load();
}

QString DataManager::storagePath(const QString &filePath) const
{
    if (!filePath.isEmpty()) {
        return filePath;
    }

    const QString appDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(appDir);
    return appDir + "/heartlight.ett";
}

bool DataManager::load(const QString &filePath)
{
    const QString path = storagePath(filePath);
    QFile dataFile(path);
    if (!dataFile.exists()) {
        m_records.clear();
        return save(path);
    }

    if (!dataFile.open(QFile::ReadOnly)) {
        return false;
    }

    const QByteArray encrypted = dataFile.readAll();
    dataFile.close();
    const QByteArray decrypted = decrypt(encrypted);
    const QJsonDocument document = QJsonDocument::fromJson(decrypted);
    if (!document.isObject()) {
        return false;
    }

    m_records.clear();
    const QJsonArray list = document.object().value("records").toArray();
    for (const QJsonValue &value : list) {
        if (value.isObject()) {
            m_records.append(jsonToRecord(value.toObject()));
        }
    }
    emit recordsChanged();
    return true;
}

bool DataManager::save(const QString &filePath)
{
    const QString path = storagePath(filePath);
    QFile dataFile(path);
    if (!dataFile.open(QFile::WriteOnly)) {
        return false;
    }

    QJsonArray list;
    for (const Record &record : m_records) {
        list.append(recordToJson(record));
    }

    QJsonObject root;
    root["records"] = list;
    root["updated"] = QDateTime::currentDateTimeUtc().toString(Qt::ISODate);
    const QJsonDocument document(root);
    const QByteArray encrypted = encrypt(document.toJson(QJsonDocument::Compact));
    dataFile.write(encrypted);
    dataFile.close();
    emit recordsChanged();
    return true;
}

bool DataManager::addRecord(const Record &record)
{
    m_records.prepend(record);
    return save();
}

bool DataManager::updateRecord(const Record &record)
{
    for (Record &item : m_records) {
        if (item.id == record.id) {
            item = record;
            return save();
        }
    }
    return false;
}

bool DataManager::removeRecord(const QString &recordId)
{
    const int originalSize = m_records.size();
    m_records.erase(std::remove_if(m_records.begin(), m_records.end(), [&](const Record &item) {
        return item.id == recordId;
    }), m_records.end());
    if (m_records.size() == originalSize) {
        return false;
    }
    return save();
}

QVector<Record> DataManager::allRecords() const
{
    return m_records;
}

QVector<Record> DataManager::search(const QString &query, const QString &timeFilter) const
{
    const QString lowerQuery = query.trimmed().toLower();
    const QDateTime now = QDateTime::currentDateTime();
    QVector<Record> result;
    for (const Record &record : m_records) {
        bool matchQuery = lowerQuery.isEmpty() || record.content.toLower().contains(lowerQuery) || record.mood.toLower().contains(lowerQuery);
        if (!matchQuery) {
            continue;
        }

        bool matchTime = true;
        if (timeFilter == QLatin1String("Today")) {
            matchTime = record.timestamp.date() == now.date();
        } else if (timeFilter == QLatin1String("This Week")) {
            const auto startOfWeek = now.addDays(-static_cast<int>(now.date().dayOfWeek()) + 1);
            matchTime = record.timestamp >= startOfWeek;
        } else if (timeFilter == QLatin1String("This Month")) {
            matchTime = record.timestamp.date().month() == now.date().month() && record.timestamp.date().year() == now.date().year();
        }

        if (matchTime) {
            result.append(record);
        }
    }
    return result;
}

bool DataManager::exportToTxt(const QString &path) const
{
    QFile outFile(path);
    if (!outFile.open(QFile::WriteOnly | QFile::Text)) {
        return false;
    }

    QTextStream stream(&outFile);
    for (const Record &record : m_records) {
        stream << record.timestamp.toString(Qt::ISODate) << "\n";
        stream << record.mood << " | " << record.type << "\n";
        stream << record.content << "\n\n";
    }
    outFile.close();
    return true;
}

bool DataManager::backupToFile(const QString &path) const
{
    return QFile::copy(storagePath(), path);
}

bool DataManager::restoreFromFile(const QString &path)
{
    const QString dest = storagePath();
    if (QFile::exists(dest)) {
        QFile::remove(dest);
    }
    if (!QFile::copy(path, dest)) {
        return false;
    }
    return load(dest);
}

QString DataManager::dataFilePath() const
{
    return storagePath();
}

QByteArray DataManager::encrypt(const QByteArray &plain) const
{
    QByteArray result = plain;
    for (int i = 0; i < result.size(); ++i) {
        result[i] = result[i] ^ m_secretKey.at(i % m_secretKey.size());
    }
    return result.toBase64();
}

QByteArray DataManager::decrypt(const QByteArray &cipher) const
{
    const QByteArray decoded = QByteArray::fromBase64(cipher);
    QByteArray result = decoded;
    for (int i = 0; i < result.size(); ++i) {
        result[i] = result[i] ^ m_secretKey.at(i % m_secretKey.size());
    }
    return result;
}

QJsonObject DataManager::recordToJson(const Record &record) const
{
    QJsonObject object;
    object["id"] = record.id;
    object["content"] = record.content;
    object["mood"] = record.mood;
    object["type"] = record.type;
    object["timestamp"] = record.timestamp.toString(Qt::ISODate);
    object["hasAttachment"] = record.hasAttachment;
    return object;
}

Record DataManager::jsonToRecord(const QJsonObject &obj) const
{
    Record record;
    record.id = obj.value("id").toString();
    record.content = obj.value("content").toString();
    record.mood = obj.value("mood").toString();
    record.type = obj.value("type").toString();
    record.timestamp = QDateTime::fromString(obj.value("timestamp").toString(), Qt::ISODate);
    record.hasAttachment = obj.value("hasAttachment").toBool();
    return record;
}
