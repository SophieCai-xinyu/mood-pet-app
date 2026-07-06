#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QDateTime>
#include <QJsonObject>
#include <QVector>

struct Record
{
    QString id;
    QString content;
    QString mood;
    QString type;
    QDateTime timestamp;
    bool hasAttachment = false;
    bool hasAlarm = false;
    QDateTime alarmTime;
};

class DataManager : public QObject
{
    Q_OBJECT

public:
    explicit DataManager(QObject *parent = nullptr);
    bool load(const QString &filePath = QString());
    bool save(const QString &filePath = QString());
    bool addRecord(const Record &record);
    bool updateRecord(const Record &record);
    bool removeRecord(const QString &recordId);
    QVector<Record> allRecords() const;
    QVector<Record> search(const QString &query, const QString &timeFilter) const;
    bool exportToTxt(const QString &path) const;
    bool backupToFile(const QString &path) const;
    bool restoreFromFile(const QString &path);
    QString dataFilePath() const;

signals:
    void recordsChanged();

private:
    QString storagePath(const QString &filePath = QString()) const;
    QByteArray encrypt(const QByteArray &plain) const;
    QByteArray decrypt(const QByteArray &cipher) const;
    QJsonObject recordToJson(const Record &record) const;
    Record jsonToRecord(const QJsonObject &obj) const;
    void ensureEncryptionKey();

    QVector<Record> m_records;
    QByteArray m_secretKey;
};

#endif // DATAMANAGER_H