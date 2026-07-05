#include "mainwindow.h"
#include "InputWindow.h"
#include "PetWidget.h"
#include "HistoryWindow.h"
#include "TrayManager.h"

#include <QAction>
#include <QFontDialog>
#include <QInputDialog>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
#include <QColorDialog>
#include <QSettings>
#include <QCryptographicHash>

#ifdef Q_OS_WIN
#include <Windows.h>
#endif

// Windows hotkey identifiers
static const int HOTKEY_SHOW_INPUT = 1;
static const int HOTKEY_TOGGLE_PET = 2;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_inputWindow(new InputWindow(this))
    , m_petWidget(new PetWidget(this))
    , m_dataManager(new DataManager(this))
    , m_historyWindow(new HistoryWindow(m_dataManager, this))
    , m_trayManager(new TrayManager(m_inputWindow, m_historyWindow, m_petWidget, m_dataManager, this))
{
    setWindowTitle(tr("心光伴旅 Demo"));
    setMinimumSize(420, 320);

    auto *openInputButton = new QPushButton(tr("Open Note"), this);
    auto *openHistoryButton = new QPushButton(tr("Open History"), this);
    m_togglePetButton = new QPushButton(tr("Hide Pet"), this);
    auto *textStyleButton = new QPushButton(tr("Text Style"), this);

    const QString mainButtonStyle = "QPushButton { color: black; background-color: #d6e4ff; border: 1px solid #8faee7; border-radius: 12px; padding: 10px 14px; font-weight: 600; } QPushButton:hover { background-color: #c4d7ff; }";
    openInputButton->setStyleSheet(mainButtonStyle);
    openHistoryButton->setStyleSheet(mainButtonStyle);
    m_togglePetButton->setStyleSheet(mainButtonStyle);
    textStyleButton->setStyleSheet(mainButtonStyle);

    connect(openInputButton, &QPushButton::clicked, this, &MainWindow::showInputWindow);
    connect(openHistoryButton, &QPushButton::clicked, this, &MainWindow::showHistoryWindowProtected);

    connect(m_togglePetButton, &QPushButton::clicked, [this]() {
        togglePetVisibility();
    });

    connect(textStyleButton, &QPushButton::clicked, [this]() {
        QSettings s;
        QFont initFont;
        initFont.fromString(s.value("ui/textFont", QFont("Arial", 14).toString()).toString());
        bool fontOk = false;
        const QFont chosenFont = QFontDialog::getFont(&fontOk, initFont, this, tr("Choose text style"));
        if (!fontOk) {
            return;
        }

        const QColor initColor = QColor::fromString(s.value("ui/textColor", QString("#000000")).toString());
        const QColor chosenColor = QColorDialog::getColor(initColor, this, tr("Choose text color"));
        if (!chosenColor.isValid()) {
            return;
        }

        s.setValue("ui/textFont", chosenFont.toString());
        s.setValue("ui/textColor", chosenColor.name());
        m_inputWindow->setTextFont(chosenFont);
        m_inputWindow->setTextColor(chosenColor);
        applyTextColorToUi(chosenColor);
    });

    connect(m_inputWindow, &InputWindow::recordSaved, this, &MainWindow::handleRecordSaved);
    connect(m_inputWindow, &InputWindow::windowShowed, m_petWidget, &PetWidget::setStateRecording);
    connect(m_inputWindow, &InputWindow::windowHided, m_petWidget, &PetWidget::setStateIdle);
    connect(m_petWidget, &PetWidget::petClicked, this, &MainWindow::handlePetClicked);
    connect(m_petWidget, &PetWidget::openInputRequested, this, &MainWindow::showInputWindow);
    connect(m_dataManager, &DataManager::recordsChanged, this, &MainWindow::refreshHistory);
    connect(m_trayManager, &TrayManager::showHistoryWindowRequested, this, &MainWindow::showHistoryWindowProtected);
    connect(m_trayManager, &TrayManager::todayRecordsRequested, this, &MainWindow::showTodayRecords);

    auto *central = new QWidget(this);
    auto *layout = new QVBoxLayout(central);
    layout->addWidget(openInputButton);
    layout->addWidget(openHistoryButton);
    layout->addWidget(m_togglePetButton);
    layout->addWidget(textStyleButton);
    layout->addStretch(1);
    layout->setContentsMargins(18, 18, 18, 18);

    setCentralWidget(central);

    m_historyWindow->refreshRecords();
    m_petWidget->show();
    m_trayManager->initialize();

    registerGlobalHotkeys();

    central->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #dae8ff, stop:0.5 #d7e2ff, stop:1 #f4f7ff);");
    setStyleSheet("QMainWindow { background: transparent; } QLabel { color: #1b2d45; } QLineEdit, QTextEdit { color: #081a33; background: rgba(255,255,255,0.95); border: 1px solid #c9d8f4; border-radius: 10px; } ");

    m_alarmTimer = new QTimer(this);
    connect(m_alarmTimer, &QTimer::timeout, this, &MainWindow::checkAlarms);
    m_alarmTimer->start(1000);

    showWelcomeGuide();
}

void MainWindow::registerGlobalHotkeys()
{
#ifdef Q_OS_WIN
    HWND hwnd = reinterpret_cast<HWND>(winId());
    RegisterHotKey(hwnd, HOTKEY_SHOW_INPUT, MOD_CONTROL | MOD_ALT, 'N');
    RegisterHotKey(hwnd, HOTKEY_TOGGLE_PET, MOD_CONTROL | MOD_ALT, 'P');
#else
    Q_UNUSED(this);
#endif
}

#ifdef Q_OS_WIN
bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, qintptr *result)
{
    if (eventType == "windows_generic_MSG") {
        MSG *msg = static_cast<MSG *>(message);
        if (msg->message == WM_HOTKEY) {
            if (msg->wParam == HOTKEY_SHOW_INPUT) {
                showInputWindow();
                return true;
            }
            if (msg->wParam == HOTKEY_TOGGLE_PET) {
                togglePetVisibility();
                return true;
            }
        }
    }
    return QMainWindow::nativeEvent(eventType, message, result);
}
#endif

void MainWindow::showWelcomeGuide()
{
    QSettings s;
    if (s.value("ui/hasSeenWelcome", false).toBool()) {
        return;
    }
    const QString message = tr(
        "欢迎使用心光伴旅！\n\n"
        "- 点击 Open Note 写新日记。\n"
        "- 点击 Open History 查看历史记录并设置密码保护。\n"
        "- 使用 Hide Pet 隐藏 / 显示桌宠。\n"
        "- 右键单击桌宠可隐藏它；左键拖动可移动。\n"
        "- 快捷键 Ctrl+Alt+N 打开写日记界面。\n"
        "- 快捷键 Ctrl+Alt+P 切换宠物显示。\n\n"
        "首次使用时，历史记录没有密码，系统会提示你设置一个。"
    );
    QMessageBox::information(this, tr("新手指南"), message);
    s.setValue("ui/hasSeenWelcome", true);
}

void MainWindow::showHistoryWindowProtected()
{
    QSettings s;
    const QString savedHash = s.value("security/passwordHash", QString()).toString();
    if (savedHash.isEmpty()) {
        bool ok = false;
        const QString first = QInputDialog::getText(this, tr("Set History Password"), tr("Please set a password to protect notes:"), QLineEdit::Password, QString(), &ok);
        if (!ok || first.isEmpty()) {
            return;
        }
        const QString second = QInputDialog::getText(this, tr("Confirm Password"), tr("Confirm your password:"), QLineEdit::Password, QString(), &ok);
        if (!ok || second.isEmpty() || first != second) {
            QMessageBox::warning(this, tr("Password Mismatch"), tr("Passwords do not match or were canceled. Please try again."));
            return;
        }
        const QByteArray hash = QCryptographicHash::hash(first.toUtf8(), QCryptographicHash::Sha256);
        s.setValue("security/passwordHash", QString::fromLatin1(hash.toHex()));
        QMessageBox::information(this, tr("Password Set"), tr("Your note history is now protected."));
    }

    const QString storedHash = s.value("security/passwordHash").toString();
    bool ok = false;
    const QString text = QInputDialog::getText(this, tr("Access Notes"), tr("Enter password to view notes:"), QLineEdit::Password, QString(), &ok);
    if (!ok) {
        return;
    }
    const QByteArray inputHash = QCryptographicHash::hash(text.toUtf8(), QCryptographicHash::Sha256);
    if (QString::fromLatin1(inputHash.toHex()) != storedHash) {
        QMessageBox::warning(this, tr("Access Denied"), tr("Incorrect password. History access is locked."));
        return;
    }
    m_historyWindow->show();
    m_historyWindow->raise();
    m_historyWindow->activateWindow();
}

void MainWindow::togglePetVisibility()
{
    if (m_petVisible) {
        m_petWidget->hide();
    } else {
        m_petWidget->show();
        m_petWidget->raise();
    }
    m_petVisible = !m_petVisible;
    if (m_togglePetButton) {
        m_togglePetButton->setText(m_petVisible ? tr("Hide Pet") : tr("Show Pet"));
    }
}

MainWindow::~MainWindow()
{
#ifdef Q_OS_WIN
    HWND hwnd = reinterpret_cast<HWND>(winId());
    UnregisterHotKey(hwnd, HOTKEY_SHOW_INPUT);
    UnregisterHotKey(hwnd, HOTKEY_TOGGLE_PET);
#endif
}

void MainWindow::showInputWindow()
{
    m_inputWindow->showInputWindow();
}

void MainWindow::handleRecordSaved(const Record &record)
{
    m_dataManager->addRecord(record);
    m_petWidget->setMood(record.mood);
    m_petWidget->setStateSuccess();
    QTimer::singleShot(1800, m_petWidget, &PetWidget::setStateIdle);
    if (record.hasAlarm) {
        ActiveAlarm alarm;
        alarm.id = record.id;
        alarm.content = record.content;
        alarm.alarmTime = record.alarmTime;
        m_activeAlarms.append(alarm);
    }
}

void MainWindow::handlePetClicked()
{
    m_petWidget->setStateNormal();
}

void MainWindow::applyTextColorToUi(const QColor &c)
{
    const QString colorName = c.name();
    const QString combined = QString(
        "QMainWindow { background: transparent; } "
        "QLabel { color: %1; } "
        "QLineEdit, QTextEdit { color: #081a33; background: rgba(255,255,255,0.95); border: 1px solid #c9d8f4; border-radius: 10px; } "
        "QPushButton { color: %1; }"
    ).arg(colorName);
    this->setStyleSheet(combined);
}

void MainWindow::showTodayRecords()
{
    m_historyWindow->setTimeFilter(tr("Today"));
    showHistoryWindowProtected();
}

void MainWindow::refreshHistory()
{
    m_historyWindow->refreshRecords();
}

void MainWindow::checkAlarms()
{
    if (m_activeAlarms.isEmpty()) {
        return;
    }

    QDateTime now = QDateTime::currentDateTime();

    for (int i = 0; i < m_activeAlarms.size(); ++i) {
        if (now >= m_activeAlarms[i].alarmTime) {
            ActiveAlarm alarm = m_activeAlarms.takeAt(i);
            --i;

            QMessageBox *alarmBox = new QMessageBox(this);
            alarmBox->setWindowTitle(tr("⏰ Time to Review Note"));
            alarmBox->setText(tr("<b>✨ Hello! It's time for your scheduled reminder:</b><br><br>%1").arg(alarm.content));
            alarmBox->setIcon(QMessageBox::Information);
            alarmBox->setWindowFlags(alarmBox->windowFlags() | Qt::WindowStaysOnTopHint);
            alarmBox->setAttribute(Qt::WA_DeleteOnClose);
            alarmBox->show();
            alarmBox->raise();
            alarmBox->activateWindow();

            if (m_petWidget) {
                m_petWidget->setMood("Focused");
            }
        }
    }
}