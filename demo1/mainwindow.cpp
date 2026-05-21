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
#include <QShortcut>
#include <QTimer>
#include <QVBoxLayout>
#include <QColorDialog>
#include <QSettings>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_inputWindow(new InputWindow)
    , m_petWidget(new PetWidget)
    , m_dataManager(new DataManager(this))
    , m_historyWindow(new HistoryWindow(m_dataManager))
    , m_trayManager(new TrayManager(m_inputWindow, m_historyWindow, m_petWidget, m_dataManager, this))
{
    setWindowTitle(tr("心光伴旅 Demo"));
    setMinimumSize(420, 320);

    auto *openInputButton = new QPushButton(tr("Open Note"), this);
    auto *openHistoryButton = new QPushButton(tr("Open History"), this);
    auto *togglePetButton = new QPushButton(tr("Hide Pet"), this);
    auto *textStyleButton = new QPushButton(tr("Text Style"), this);

    const QString mainButtonStyle = "QPushButton { color: black; background-color: #d6e4ff; border: 1px solid #8faee7; border-radius: 12px; padding: 10px 14px; font-weight: 600; } QPushButton:hover { background-color: #c4d7ff; }";
    openInputButton->setStyleSheet(mainButtonStyle);
    openHistoryButton->setStyleSheet(mainButtonStyle);
    togglePetButton->setStyleSheet(mainButtonStyle);
    textStyleButton->setStyleSheet(mainButtonStyle);

    connect(openInputButton, &QPushButton::clicked, this, &MainWindow::showInputWindow);
    connect(openHistoryButton, &QPushButton::clicked, this, &MainWindow::showHistoryWindowProtected);

    connect(togglePetButton, &QPushButton::clicked, [this, togglePetButton]() {
        togglePetVisibility();
        togglePetButton->setText(m_petVisible ? tr("Hide Pet") : tr("Show Pet"));
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
    connect(m_dataManager, &DataManager::recordsChanged, this, &MainWindow::refreshHistory);
    connect(m_trayManager, &TrayManager::showHistoryWindowRequested, this, &MainWindow::showHistoryWindowProtected);

    auto *central = new QWidget(this);
    auto *layout = new QVBoxLayout(central);
    layout->addWidget(openInputButton);
    layout->addWidget(openHistoryButton);
    layout->addWidget(togglePetButton);
    layout->addWidget(textStyleButton);
    layout->addStretch(1);
    layout->setContentsMargins(18, 18, 18, 18);

    setCentralWidget(central);

    m_historyWindow->refreshRecords();
    m_petWidget->show();
    m_trayManager->initialize();

    auto *shortcut = new QShortcut(QKeySequence(tr("Ctrl+Alt+N")), this);
    connect(shortcut, &QShortcut::activated, this, &MainWindow::showInputWindow);

    auto *petShortcut = new QShortcut(QKeySequence(tr("Ctrl+Alt+P")), this);
    connect(petShortcut, &QShortcut::activated, [this]() {
        togglePetVisibility();
    });

    // Background gradient for central widget
    central->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #dae8ff, stop:0.5 #d7e2ff, stop:1 #f4f7ff);");
    setStyleSheet("QMainWindow { background: transparent; } QLabel { color: #1b2d45; } QLineEdit, QTextEdit { color: #081a33; background: rgba(255,255,255,0.95); border: 1px solid #c9d8f4; border-radius: 10px; } ");

    showWelcomeGuide();
}

void MainWindow::showWelcomeGuide()
{
    QSettings s;
    if (s.value("ui/hasSeenWelcome", false).toBool()) {
        return;
    }

    const QString message = tr(
        "欢迎使用心光伴旅！\n\n"
        "- 点击 “Open Note” 写新日记。\n"
        "- 点击 “Open History” 查看历史记录并设置密码保护。\n"
        "- 使用 “Hide Pet” 隐藏 / 显示桌宠。\n"
        "- 右键单击桌宠可隐藏它；左键拖动可移动。\n"
        "- 快捷键 Ctrl+Alt+N 打开写日记界面。\n\n"
        "首次使用时，历史记录没有密码，系统会提示你设置一个。"
    );

    QMessageBox::information(this, tr("新手指南"), message);
    s.setValue("ui/hasSeenWelcome", true);
}

void MainWindow::showHistoryWindowProtected()
{
    QSettings s;
    const QString savedPassword = s.value("security/password", QString()).toString();
    if (savedPassword.isEmpty()) {
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
        s.setValue("security/password", first);
        QMessageBox::information(this, tr("Password Set"), tr("Your note history is now protected."));
    }

    const QString password = s.value("security/password").toString();
    bool ok = false;
    const QString text = QInputDialog::getText(this, tr("Access Notes"), tr("Enter password to view notes:"), QLineEdit::Password, QString(), &ok);
    if (!ok) {
        return;
    }
    if (text != password) {
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
}

MainWindow::~MainWindow() = default;

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
}

void MainWindow::handlePetClicked()
{
    m_petWidget->setStateNormal();
}

void MainWindow::applyTextColorToUi(const QColor &c)
{
    const QString colorName = c.name();
    // apply to labels and buttons
    const QString btnStyle = QString("color: %1;").arg(colorName);
    // naive: set palette on central widget children via style
    this->setStyleSheet(QString("QPushButton { %1 } QLabel { color: %2 }").arg(btnStyle, colorName));
}

void MainWindow::refreshHistory()
{
    m_historyWindow->refreshRecords();
}
