#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DataManager.h"
#include <QTimer>
#include <QDateTime>
#include <QList>

class QColor;
class QPushButton;
class InputWindow;
class PetWidget;
class HistoryWindow;
class TrayManager;

struct ActiveAlarm {
    QString id;
    QString content;
    QDateTime alarmTime;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

public slots:
    void showInputWindow();
    void togglePetVisibility();
    void showTodayRecords();

private slots:
    void showHistoryWindowProtected();
    void handleRecordSaved(const Record &record);
    void handlePetClicked();
    void refreshHistory();
    void checkAlarms();

protected:
#ifdef Q_OS_WIN
    bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result) override;
#endif

private:
    void registerGlobalHotkeys();
    void applyTextColorToUi(const QColor &c);
    void showWelcomeGuide();

    InputWindow *m_inputWindow;
    PetWidget *m_petWidget;
    DataManager *m_dataManager;
    HistoryWindow *m_historyWindow;
    TrayManager *m_trayManager;
    QPushButton *m_togglePetButton = nullptr;
    bool m_petVisible = true;
    QTimer *m_alarmTimer;
    QList<ActiveAlarm> m_activeAlarms;
};

#endif // MAINWINDOW_H