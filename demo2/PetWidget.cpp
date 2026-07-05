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
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);
    setFixedSize(180, 180);

    m_display->setAlignment(Qt::AlignCenter);
    m_display->setWordWrap(true);
    m_display->setStyleSheet("color: white; font-size: 28px; font-weight: bold;");
    m_display->setMovie(m_movie);

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(m_display);
    layout->setContentsMargins(10, 10, 10, 10);
    setLayout(layout);

    m_gifs = {"pet1.gif", "pet2.gif", "pet3.gif", "pet4.gif"};

    m_bubble->setVisible(false);
    m_bubble->setStyleSheet("background: rgba(255, 255, 255, 0.95); color: #111; border: 1px solid rgba(0,0,0,0.12); border-radius: 10px; padding: 8px 10px; font-size: 12px;");
    m_bubble->setAttribute(Qt::WA_TransparentForMouseEvents);
    m_bubbleTimer->setSingleShot(true);
    connect(m_bubbleTimer, &QTimer::timeout, m_bubble, &QLabel::hide);

    setMood(m_mood);
}

PetWidget::~PetWidget() = default;

void PetWidget::setStateIdle()
{
    // no extra state behavior needed for simplified pet widget
}

void PetWidget::setStateNormal()
{
    // no extra state behavior needed for simplified pet widget
}

void PetWidget::setStateRecording()
{
    // no extra state behavior needed for simplified pet widget
}

void PetWidget::setStateSuccess()
{
    // no extra state behavior needed for simplified pet widget
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

        const QStringList tips = {
            tr("你很棒！"),
            tr("继续保持~"),
            tr("写点东西试试？"),
            tr("来，给自己一个微笑。")
        };
        const int index = QRandomGenerator::global()->bounded(tips.size());
        m_bubble->setText(tips.at(index));
        m_bubble->adjustSize();
        const int bx = width() - m_bubble->width() - 12;
        const int by = 12;
        m_bubble->move(bx, by);
        m_bubble->raise();
        m_bubble->show();
        m_bubbleTimer->start(1000);

        if (!m_gifs.isEmpty()) {
            int randomIndex = QRandomGenerator::global()->bounded(m_gifs.size());
            QString randomGif = m_gifs.at(randomIndex);
            loadLocalMovie(randomGif);
        }

        event->accept();
    }
}

void PetWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    QWidget::mouseDoubleClickEvent(event);
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
