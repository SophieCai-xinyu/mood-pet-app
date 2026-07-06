#include "PetWidget.h"

#include <QLabel>
#include <QMouseEvent>
#include <QMovie>
#include <QPoint>
#include <QTimer>
#include <QVBoxLayout>
#include <QRandomGenerator>
#include <QFile>
#include <QCoreApplication>
#include <QDir>
#include <QStringList>
#include <QPainter>

static QString toLocalPetPath(const QString &filename)
{
    const QString appDir = QCoreApplication::applicationDirPath();
    const QStringList candidates = {
        QStringLiteral("%1/pet/%2").arg(appDir, filename),
        QStringLiteral("%1/../pet/%2").arg(appDir, filename),
        QStringLiteral("%1/../../pet/%2").arg(appDir, filename),
        QStringLiteral("%1/../../../pet/%2").arg(appDir, filename),
        QStringLiteral("./pet/%2").arg(filename)
    };

    for (const QString &path : candidates) {
        if (QFile::exists(path)) {
            return QDir(path).canonicalPath();
        }
    }

    QDir currentDir(QDir::currentPath());
    for (int i = 0; i < 4; ++i) {
        const QString candidate = currentDir.filePath(QStringLiteral("pet/%1").arg(filename));
        if (QFile::exists(candidate)) {
            return QDir(candidate).canonicalPath();
        }
        if (!currentDir.cdUp()) {
            break;
        }
    }
    return QString();
}

PetWidget::PetWidget(QWidget *parent)
    : QWidget(parent)
    , m_mood(tr("Neutral"))
    , m_display(new QLabel(this))
    , m_movie(new QMovie(this))
    , m_bubble(new QLabel(this))
    , m_bubbleTimer(new QTimer(this))
{
    setObjectName("PetWidget");
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::NoDropShadowWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);
    setFixedSize(150, 195);

    m_display->setAlignment(Qt::AlignCenter);
    m_display->setScaledContents(true);
    m_display->setMargin(0);
    m_display->setIndent(0);
    m_display->setStyleSheet("color: white; font-size: 14px; font-weight: bold; padding: 0px;");
    m_display->setMovie(m_movie);
    m_display->setGeometry(0, 45, 150, 150);

    m_gifs = {"pet1.gif", "pet2.gif", "pet3.gif", "pet4.gif"};

    m_bubble->setVisible(false);
    m_bubble->setStyleSheet("background: rgba(255, 255, 255, 0.95); color: #111; border: 1px solid rgba(0,0,0,0.12); border-radius: 10px; padding: 8px 10px; font-size: 12px;");
    m_bubble->setAttribute(Qt::WA_TransparentForMouseEvents);
    m_bubbleTimer->setSingleShot(true);
    connect(m_bubbleTimer, &QTimer::timeout, m_bubble, &QLabel::hide);

    // GIF adaptive sizing
    connect(m_movie, &QMovie::frameChanged, this, [this](int frameNumber) {
        Q_UNUSED(frameNumber);
        QSize gifSize = m_movie->frameRect().size();
        if (gifSize.isValid() && gifSize.width() > 0 && gifSize.height() > 0) {
            const int bubbleZone = 45;
            const int newW = qMax(150, gifSize.width());
            const int newH = bubbleZone + gifSize.height();
            if (this->size() != QSize(newW, newH)) {
                setFixedSize(newW, newH);
                m_display->setGeometry(0, bubbleZone, gifSize.width(), gifSize.height());
            }
        }
        this->update();
    });

    setMood(m_mood);
}

PetWidget::~PetWidget() = default;

void PetWidget::setStateIdle()
{
    if (!m_gifs.isEmpty()) {
        const int idx = QRandomGenerator::global()->bounded(m_gifs.size());
        if (loadLocalMovie(m_gifs.at(idx))) {
            showDailyQuoteIfFirst();
            return;
        }
    }
    m_display->setText(tr("😴\n%1").arg(m_mood));
}

void PetWidget::setStateNormal()
{
    m_movie->stop();
    m_display->setText(tr("😺\n%1").arg(m_mood));
}

void PetWidget::setStateRecording()
{
    if (m_gifs.size() >= 2) {
        if (loadLocalMovie(m_gifs.at(1))) {
            return;
        }
    }
    m_display->setText(tr("✍️\n%1").arg(m_mood));
}

void PetWidget::setStateSuccess()
{
    if (!m_gifs.isEmpty()) {
        if (loadLocalMovie(m_gifs.at(0))) {
            return;
        }
    }
    m_display->setText(tr("🎉\n%1").arg(m_mood));
}

static const QStringList kDailyQuotes = {
    QStringLiteral("今天的你，已经很棒了。"),
    QStringLiteral("慢慢来，一切都会好起来。"),
    QStringLiteral("你已经做得很好了。"),
    QStringLiteral("允许自己偶尔停下来。"),
    QStringLiteral("你是被认真爱着的人。"),
    QStringLiteral("每一步都在靠近你想要的明天。"),
    QStringLiteral("没关系，天会亮的。"),
    QStringLiteral("今天比昨天又多走了一步。"),
    QStringLiteral("你不需要对所有人好，先照顾好自己。"),
    QStringLiteral("喘口气，世界不会倒塌。"),
    QStringLiteral("即使现在不太顺利，也不代表失败。"),
    QStringLiteral("你的感受是重要的。"),
    QStringLiteral("今天也谢谢你陪着自己。"),
    QStringLiteral("不是每天都要完美，及格也可以。"),
    QStringLiteral("别把别人的课题扛在自己肩上。"),
    QStringLiteral("你值得被温柔对待。"),
    QStringLiteral("做件小事，小小的成就感也好。"),
    QStringLiteral("有时候，什么都不做也可以。"),
    QStringLiteral("今天你微笑了吗？哪怕只是尝试一下。"),
    QStringLiteral("你是这个世界上独一无二的光。")
};

void PetWidget::showDailyQuoteIfFirst()
{
    QSettings s;
    const QString today = QDate::currentDate().toString(Qt::ISODate);
    const QString last = s.value("dailyQuote/lastDate", QString()).toString();
    if (last == today) {
        return;
    }

    int lastIdx = s.value("dailyQuote/lastIndex", -1).toInt();
    int idx = QRandomGenerator::global()->bounded(kDailyQuotes.size());
    if (kDailyQuotes.size() > 1 && idx == lastIdx) {
        idx = (idx + 1) % kDailyQuotes.size();
    }

    s.setValue("dailyQuote/lastDate", today);
    s.setValue("dailyQuote/lastIndex", idx);

    m_bubble->setMinimumWidth(0);
    m_bubble->setMaximumWidth(width() - 8);
    m_bubble->setText(kDailyQuotes.at(idx));
    m_bubble->adjustSize();
    const int bx = qMax(0, (width() - m_bubble->width()) / 2);
    const int by = qMax(0, 45 - m_bubble->height());
    m_bubble->move(bx, by);
    m_bubble->raise();
    m_bubble->show();
    m_bubbleTimer->start(3000);
}

void PetWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton) {
        hide();
        event->accept();
        return;
    }

    if (event->button() == Qt::LeftButton) {
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        emit petClicked();
        emit openInputRequested();

        const QStringList tips = {
            tr("你很棒！"),
            tr("继续保持~"),
            tr("写点东西试试？"),
            tr("来，给自己一个微笑。")
        };
        const int index = QRandomGenerator::global()->bounded(tips.size());
        m_bubble->setMinimumWidth(0);
        m_bubble->setMaximumWidth(width() - 8);
        m_bubble->setText(tips.at(index));
        m_bubble->adjustSize();
        const int bx = qMax(0, (width() - m_bubble->width()) / 2);
        const int by = qMax(0, 45 - m_bubble->height());
        m_bubble->move(bx, by);
        m_bubble->raise();
        m_bubble->show();
        m_bubbleTimer->start(1000);

        if (!m_gifs.isEmpty()) {
            int randomIndex = QRandomGenerator::global()->bounded(m_gifs.size());
            QString randomGif = m_gifs.at(randomIndex);
            if (!loadLocalMovie(randomGif)) {
                m_display->setText(tr("😺\n%1").arg(m_mood));
            }
        }

        event->accept();
    }
}

void PetWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPosition().toPoint() - m_dragPosition);
        event->accept();
    } else {
        QWidget::mouseMoveEvent(event);
    }
}

void PetWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    setAttribute(Qt::WA_TranslucentBackground, true);

    if (m_movie) {
        QSize gifSize = m_movie->frameRect().size();
        if (gifSize.isValid() && gifSize.width() > 0 && gifSize.height() > 0) {
            const int bubbleZone = 45;
            const int newW = qMax(150, gifSize.width());
            const int newH = bubbleZone + gifSize.height();
            setFixedSize(newW, newH);
            m_display->setGeometry(0, bubbleZone, gifSize.width(), gifSize.height());
        }
    }

    this->update();
}
void PetWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.fillRect(this->rect(), Qt::transparent);
}

bool PetWidget::loadLocalMovie(const QString &filename)
{
    const QString path = toLocalPetPath(filename);
    if (path.isEmpty()) {
        return false;
    }

    m_movie->stop();
    m_movie->setFileName(path);
    m_movie->start();

    if (m_movie->isValid()) {
        m_display->setMovie(m_movie);
        return true;
    }

    m_movie->stop();
    return false;
}

void PetWidget::setMood(const QString &mood)
{
    m_mood = mood;
    const QString low = mood.toLower();
    QString gifName;
    if (low.contains("sad") || low.contains("angry") || low.contains("unhappy") || low.contains("hurt") || low.contains("bad")) {
        gifName = "pet_sleep.gif";
    } else {
        if (!m_gifs.isEmpty()) {
            const int idx = QRandomGenerator::global()->bounded(m_gifs.size());
            gifName = m_gifs.at(idx);
        }
    }

    if (!gifName.isEmpty() && loadLocalMovie(gifName)) {
        return;
    }

    // fallback text label when gif fails
    m_display->setText(tr("😺\n%1").arg(m_mood));
}