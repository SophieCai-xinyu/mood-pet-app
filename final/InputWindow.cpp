#include "InputWindow.h"
#include "DataManager.h"

#include <QApplication>
#include <QComboBox>
#include <QDateTime>
#include <QFile>
#include <QFont>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QLabel>
#include <QLineEdit>
#include <QMouseEvent>
#include <QPushButton>
#include <QTextEdit>
#include <QUuid>
#include <QVBoxLayout>
#include <QSettings>

#include <QColor>

InputWindow::InputWindow(QWidget *parent)
    : QWidget(parent)
    , m_noteInput(new QTextEdit(this))
    , m_moodBox(new QComboBox(this))
    , m_saveButton(new QPushButton(tr("Save"), this))
    , m_clearButton(new QPushButton(tr("Clear"), this))
    , m_hideButton(new QPushButton(tr("Hide"), this))
    , m_currentMood(tr("Neutral"))
    , m_textColor(Qt::white)
    , m_textFont(QFont("Arial", 14))
{
    setObjectName("InputWindow");
    setWindowTitle(tr("Note"));
    setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_DeleteOnClose, false);

    createLayout();
    loadStyleSheet();

    // load saved text color and font
    QSettings s;
    const QVariant colorVar = s.value("ui/textColor");
    if (colorVar.isValid()) {
        const QColor c(colorVar.toString());
        if (c.isValid()) {
            setTextColor(c);
        }
    }
    const QString fontString = s.value("ui/textFont", m_textFont.toString()).toString();
    if (!fontString.isEmpty()) {
        QFont savedFont;
        savedFont.fromString(fontString);
        if (!savedFont.family().isEmpty()) {
            setTextFont(savedFont);
        }
    }

    m_titleLabel->installEventFilter(this);
    m_noteInput->installEventFilter(this);
    connect(m_saveButton, &QPushButton::clicked, this, &InputWindow::onSaveClicked);
    connect(m_clearButton, &QPushButton::clicked, this, &InputWindow::onClearClicked);
    connect(m_hideButton, &QPushButton::clicked, this, &InputWindow::hideInputWindow);
    connect(m_moodBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &InputWindow::onMoodChanged);
}

InputWindow::~InputWindow() = default;

void InputWindow::createLayout()
{
    m_titleLabel = new QLabel(tr("Note"), this);
    m_titleLabel->setStyleSheet("color: #f5f8ff; font-size: 18px; font-weight: bold;");
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setCursor(Qt::OpenHandCursor);
    m_titleLabel->setFixedHeight(44);
    m_titleLabel->setStyleSheet(m_titleLabel->styleSheet() + "padding: 10px 0; background: rgba(20, 28, 66, 0.78); border-radius: 12px;");

    m_noteInput->setPlaceholderText(tr("Type your note here..."));
    m_noteInput->setFixedHeight(220);

    m_moodBox->addItems({tr("Neutral"), tr("Happy"), tr("Calm"), tr("Excited"), tr("Unhappy"), tr("Focused")});
    m_moodBox->setCurrentIndex(0);

    m_alarmCheckBox = new QCheckBox(tr("Remind Me (Alarm)"), this);
    m_alarmCheckBox->setStyleSheet("QCheckBox { color: #f5f8ff; font-weight: 500; }");

    m_alarmDateTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime(), this);
    m_alarmDateTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm");
    m_alarmDateTimeEdit->setCalendarPopup(true);
    m_alarmDateTimeEdit->setEnabled(false);
    m_alarmDateTimeEdit->setStyleSheet(
        "QDateTimeEdit { color: #081a33; background: rgba(255,255,255,0.95); border: 1px solid #c9d8f4; border-radius: 8px; padding: 4px; }"
        "QDateTimeEdit:disabled { background: rgba(200, 200, 200, 0.4); color: #888888; }"
        );
    connect(m_alarmCheckBox, &QCheckBox::toggled, m_alarmDateTimeEdit, &QDateTimeEdit::setEnabled);

    auto *alarmLayout = new QHBoxLayout;
    alarmLayout->addWidget(m_alarmCheckBox);
    alarmLayout->addWidget(m_alarmDateTimeEdit);
    alarmLayout->addStretch(1);

    auto *moodLabel = new QLabel(tr("Mood:"), this);
    moodLabel->setObjectName("MoodLabel");

    auto *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(m_saveButton);
    buttonLayout->addWidget(m_clearButton);
    buttonLayout->addWidget(m_hideButton);

    auto *moodLayout = new QHBoxLayout;
    moodLayout->addWidget(moodLabel);
    moodLayout->addWidget(m_moodBox);
    moodLayout->addStretch(1);

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_titleLabel);
    mainLayout->addWidget(m_noteInput);
    mainLayout->addLayout(moodLayout);
    mainLayout->addLayout(alarmLayout);
    mainLayout->addLayout(buttonLayout);
    mainLayout->setContentsMargins(14, 14, 14, 14);
    mainLayout->setSpacing(10);

    setLayout(mainLayout);
    resize(420, 360);
}

void InputWindow::loadStyleSheet()
{
    QFile styleFile(":/style.qss");
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        qApp->setStyleSheet(styleFile.readAll());
    }
}

void InputWindow::setTextColor(const QColor &color)
{
    m_textColor = color;
    applyTextStyle();
}

void InputWindow::setTextFont(const QFont &font)
{
    m_textFont = font;
    applyTextStyle();
}

void InputWindow::applyTextStyle()
{
    m_noteInput->setFont(m_textFont);
    const QString colorName = m_textColor.name(QColor::HexRgb);
    const QString style = QString("color: %1;").arg(colorName);
    m_noteInput->setStyleSheet(style);
    m_noteInput->setFont(m_textFont);
}

void InputWindow::showInputWindow()
{
    if (!isVisible()) {
        move(QCursor::pos() - QPoint(width() / 2, height() / 2));
        show();
        activateWindow();
        raise();
        emit windowShowed();
    }
}

void InputWindow::hideInputWindow()
{
    if (isVisible()) {
        QWidget::hide();
        emit windowHided();
    }
}

void InputWindow::onSaveClicked()
{
    const QString content = m_noteInput->toPlainText().trimmed();
    if (content.isEmpty()) {
        return;
    }
    Record record;
    record.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    record.content = content;
    record.mood = m_currentMood;
    record.type = tr("Note");
    record.timestamp = QDateTime::currentDateTime();
    record.hasAttachment = false;
    record.hasAlarm = m_alarmCheckBox->isChecked();
    record.alarmTime = m_alarmDateTimeEdit->dateTime();
    emit recordSaved(record);
    clearInputs();
}

void InputWindow::onClearClicked()
{
    clearInputs();
}

void InputWindow::onMoodChanged(int index)
{
    m_currentMood = m_moodBox->itemText(index);
}


void InputWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
        event->accept();
    }
}

void InputWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPosition().toPoint() - m_dragPosition);
        event->accept();
    }
}

bool InputWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == m_titleLabel && event->type() == QEvent::MouseButtonPress) {
        auto *mouseEvent = static_cast<QMouseEvent *>(event);
        mousePressEvent(mouseEvent);
        return true;
    }
    if (obj == m_titleLabel && event->type() == QEvent::MouseMove) {
        auto *mouseEvent = static_cast<QMouseEvent *>(event);
        mouseMoveEvent(mouseEvent);
        return true;
    }
    if (obj == m_noteInput) {
        if (event->type() == QEvent::FocusIn) {
            m_noteInput->setPlaceholderText("");
            return false;
        }
        if (event->type() == QEvent::FocusOut) {
            if (m_noteInput->toPlainText().trimmed().isEmpty()) {
                m_noteInput->setPlaceholderText(tr("Type your note here..."));
            }
            return false;
        }
        if (event->type() == QEvent::KeyPress) {
            auto *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
                if (keyEvent->modifiers() & Qt::ShiftModifier) {
                    return false;
                }
                onSaveClicked();
                return true;
            }
        }
    }
    return QWidget::eventFilter(obj, event);
}

void InputWindow::clearInputs()
{
    m_noteInput->clear();
    m_alarmCheckBox->setChecked(false);
    m_alarmDateTimeEdit->setDateTime(QDateTime::currentDateTime());
}
