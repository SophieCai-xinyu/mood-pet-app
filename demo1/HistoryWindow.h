#ifndef HISTORYWINDOW_H
#define HISTORYWINDOW_H

#include <QWidget>

class QLineEdit;
class QListWidget;
class QListWidgetItem;
class QPushButton;
class QComboBox;

#include "DataManager.h"

class HistoryWindow : public QWidget
{
    Q_OBJECT

public:
    explicit HistoryWindow(DataManager *manager, QWidget *parent = nullptr);
    ~HistoryWindow() override;
    void refreshRecords();
    void setTimeFilter(const QString &filter);

private slots:
    void onSearchTextChanged(const QString &text);
    void onFilterChanged(const QString &filter);
    void onItemClicked(QListWidgetItem *item);
    void onExportClicked();

private:
    void setupLayout();
    void updateList();
    Record findRecord(const QString &recordId) const;
    void showRecordDetail(const Record &record);

    DataManager *m_dataManager;
    QVector<Record> m_filteredRecords;
    QLineEdit *m_searchInput;
    QComboBox *m_timeFilter;
    QListWidget *m_listWidget;
    QPushButton *m_exportButton;
};

#endif // HISTORYWINDOW_H
