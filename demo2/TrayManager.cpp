#include "TrayManager.h"

#include "InputWindow.h"
#include "HistoryWindow.h"
#include "PetWidget.h"
#include "DataManager.h"

#include <QAction>
#include <QApplication>
#include <QFileDialog>
#include <QMenu>
#include <QSystemTrayIcon>
#include <QStyle>

TrayManager::TrayManager(InputWindow *inputWindow,
                         HistoryWindow *historyWindow,
                         PetWidget *petWidget,
                         DataManager *dataManager,
                         QObject *parent)
    : QObject(parent)
    , m_inputWindow(inputWindow)
    , m_historyWindow(historyWindow)
    , m_petWidget(petWidget)
    , m_dataManager(dataManager)
    , m_trayIcon(new QSystemTrayIcon(this))
    , m_menu(new QMenu)
{
    m_showInputAction = new QAction(tr("Open Quick Note"), this);
    m_showHistoryAction = new QAction(tr("Open History"), this);
    m_showPetAction = new QAction(tr("Show Pet"), this);
    m_hideAllAction = new QAction(tr("Hide All"), this);
    m_backupAction = new QAction(tr("Backup Data"), this);
    m_restoreAction = new QAction(tr("Restore Data"), this);
    m_quitAction = new QAction(tr("Quit"), this);

    connect(m_showInputAction, &QAction::triggered, this, &TrayManager::onShowInput);
    connect(m_showHistoryAction, &QAction::triggered, this, &TrayManager::onShowHistory);
    connect(m_showPetAction, &QAction::triggered, this, &TrayManager::onShowPet);
    connect(m_hideAllAction, &QAction::triggered, this, &TrayManager::onHideAll);
    connect(m_backupAction, &QAction::triggered, this, &TrayManager::onBackupData);
    connect(m_restoreAction, &QAction::triggered, this, &TrayManager::onRestoreData);
    connect(m_quitAction, &QAction::triggered, this, &TrayManager::onQuit);

    m_menu->addAction(m_showInputAction);
    m_menu->addAction(m_showHistoryAction);
    m_menu->addAction(m_showPetAction);
    m_menu->addAction(m_hideAllAction);
    m_menu->addSeparator();
    m_menu->addAction(m_backupAction);
    m_menu->addAction(m_restoreAction);
    m_menu->addSeparator();
    m_menu->addAction(m_quitAction);

    m_trayIcon->setContextMenu(m_menu);
    m_trayIcon->setIcon(qApp->style()->standardIcon(QStyle::SP_ComputerIcon));
    m_trayIcon->setToolTip(tr("心光伴旅 Demo"));
}

TrayManager::~TrayManager() = default;

void TrayManager::initialize()
{
    if (QSystemTrayIcon::isSystemTrayAvailable()) {
        m_trayIcon->show();
    }
}

void TrayManager::onShowInput()
{
    if (m_inputWindow) {
        m_inputWindow->showInputWindow();
    }
}

void TrayManager::onShowHistory()
{
    emit showHistoryWindowRequested();
}

void TrayManager::onShowPet()
{
    if (m_petWidget) {
        m_petWidget->show();
        m_petWidget->raise();
    }
}

void TrayManager::onHideAll()
{
    if (m_inputWindow) {
        m_inputWindow->hide();
    }
    if (m_historyWindow) {
        m_historyWindow->hide();
    }
    if (m_petWidget) {
        m_petWidget->hide();
    }
}

void TrayManager::onBackupData()
{
    const QString path = QFileDialog::getSaveFileName(nullptr, tr("Backup Data File"), QStringLiteral("heartlight-backup.ett"), tr("ETT Files (*.ett)"));
    if (path.isEmpty() || !m_dataManager) {
        return;
    }
    if (!m_dataManager->backupToFile(path)) {
        m_trayIcon->showMessage(tr("Backup Failed"), tr("Unable to create backup file."));
    } else {
        m_trayIcon->showMessage(tr("Backup Complete"), tr("Data backup saved."));
    }
}

void TrayManager::onRestoreData()
{
    const QString path = QFileDialog::getOpenFileName(nullptr, tr("Restore Data File"), QString(), tr("ETT Files (*.ett)"));
    if (path.isEmpty() || !m_dataManager) {
        return;
    }
    if (!m_dataManager->restoreFromFile(path)) {
        m_trayIcon->showMessage(tr("Restore Failed"), tr("Unable to restore the selected backup."));
    } else {
        m_trayIcon->showMessage(tr("Restore Complete"), tr("Data has been restored."));
    }
}

void TrayManager::onQuit()
{
    qApp->quit();
}
