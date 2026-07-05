#ifndef TRAYMANAGER_H
#define TRAYMANAGER_H

#include <QObject>

class QAction;
class QMenu;
class QSystemTrayIcon;
class InputWindow;
class HistoryWindow;
class PetWidget;
class DataManager;

class TrayManager : public QObject
{
    Q_OBJECT

public:
    explicit TrayManager(InputWindow *inputWindow,
                         HistoryWindow *historyWindow,
                         PetWidget *petWidget,
                         DataManager *dataManager,
                         QObject *parent = nullptr);
    ~TrayManager() override;

    void initialize();

signals:
    void showInputWindowRequested();
    void showHistoryWindowRequested();
    void showPetRequested();
    void hideAllRequested();
    void backupRequested();
    void restoreRequested();
    void quitRequested();

private slots:
    void onShowInput();
    void onShowHistory();
    void onShowPet();
    void onHideAll();
    void onBackupData();
    void onRestoreData();
    void onQuit();

private:
    InputWindow *m_inputWindow;
    HistoryWindow *m_historyWindow;
    PetWidget *m_petWidget;
    DataManager *m_dataManager;
    QSystemTrayIcon *m_trayIcon;
    QMenu *m_menu;
    QAction *m_showInputAction;
    QAction *m_showHistoryAction;
    QAction *m_showPetAction;
    QAction *m_hideAllAction;
    QAction *m_backupAction;
    QAction *m_restoreAction;
    QAction *m_quitAction;
};

#endif // TRAYMANAGER_H
