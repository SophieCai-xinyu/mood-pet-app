#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DataManager.h"
#include <QTimer>
#include <QDateTime>
#include <QList>

class QColor;
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

private slots:
    void checkAlarms();

private slots:
    void showHistoryWindowProtected();
    void handleRecordSaved(const Record &record);
    void handlePetClicked();
    void refreshHistory();

private:
    InputWindow *m_inputWindow;
    PetWidget *m_petWidget;
    DataManager *m_dataManager;
    HistoryWindow *m_historyWindow;
    TrayManager *m_trayManager;
    void applyTextColorToUi(const QColor &c);
    void togglePetVisibility();
    void showWelcomeGuide();
    bool m_petVisible = true;
    QTimer *m_alarmTimer;
    QList<ActiveAlarm> m_activeAlarms;
};

#endif // MAINWINDOW_H
