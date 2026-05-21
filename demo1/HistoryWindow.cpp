#include "HistoryWindow.h"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QInputDialog>
#include <QLabel>
#include <QListView>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include <QListWidgetItem>

HistoryWindow::HistoryWindow(DataManager *manager, QWidget *parent)
    : QWidget(parent)
    , m_dataManager(manager)
    , m_searchInput(new QLineEdit(this))
    , m_timeFilter(new QComboBox(this))
    , m_listWidget(new QListWidget(this))
    , m_exportButton(new QPushButton(tr("Export TXT"), this))
{
    setWindowTitle(tr("History Records"));
    setMinimumSize(520, 420);
    setStyleSheet("QWidget { background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #eef3ff, stop:1 #dae4ff); } QLabel { color: #1a2740; font-weight: 600; } QLineEdit, QComboBox, QListWidget { background: rgba(255,255,255,0.92); border: 1px solid #c9d8f4; border-radius: 10px; } QListWidget::item:selected { background: rgba(94, 116, 255, 0.22); } QPushButton { color: black; background: #f5f8ff; border: 1px solid #b5c6ef; border-radius: 10px; padding: 8px 12px; }");
    setupLayout();
    refreshRecords();
}

HistoryWindow::~HistoryWindow() = default;

void HistoryWindow::setupLayout()
{
    m_searchInput->setPlaceholderText(tr("Search notes, mood, content..."));
    m_timeFilter->addItems({tr("All"), tr("Today"), tr("This Week"), tr("This Month")});
    m_timeFilter->setMinimumWidth(150);
    m_timeFilter->setMaxVisibleItems(5);
    m_timeFilter->view()->setStyleSheet("QListView { color: #1a2740; background: white; } QListView::item:selected { background: rgba(94, 116, 255, 0.22); }");

    connect(m_searchInput, &QLineEdit::textChanged, this, &HistoryWindow::onSearchTextChanged);
    connect(m_timeFilter, &QComboBox::currentTextChanged, this, &HistoryWindow::onFilterChanged);
    connect(m_listWidget, &QListWidget::itemClicked, this, &HistoryWindow::onItemClicked);
    connect(m_exportButton, &QPushButton::clicked, this, &HistoryWindow::onExportClicked);

    auto *headerLabel = new QLabel(tr("History Records"), this);
    headerLabel->setStyleSheet("font-size: 18px; margin-bottom: 10px;");

    auto *filterLayout = new QHBoxLayout;
    filterLayout->addWidget(new QLabel(tr("Filter:"), this));
    filterLayout->addWidget(m_searchInput);
    filterLayout->addWidget(m_timeFilter);
    filterLayout->addWidget(m_exportButton);

    m_listWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    m_listWidget->setSpacing(4);

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(headerLabel);
    mainLayout->addLayout(filterLayout);
    mainLayout->addWidget(m_listWidget);
    mainLayout->setContentsMargins(16, 16, 16, 16);
    mainLayout->setSpacing(12);

    setLayout(mainLayout);
}

void HistoryWindow::refreshRecords()
{
    const QString query = m_searchInput->text();
    const QString filter = m_timeFilter->currentText();
    m_filteredRecords = m_dataManager->search(query, filter);
    updateList();
}

void HistoryWindow::onSearchTextChanged(const QString &)
{
    refreshRecords();
}

void HistoryWindow::onFilterChanged(const QString &)
{
    refreshRecords();
}

void HistoryWindow::onItemClicked(QListWidgetItem *item)
{
    const QString recordId = item->data(Qt::UserRole).toString();
    const Record record = findRecord(recordId);
    showRecordDetail(record);
}

void HistoryWindow::onExportClicked()
{
    const QString path = QFileDialog::getSaveFileName(this, tr("Export History as TXT"), QStringLiteral("history_export.txt"), tr("Text Files (*.txt)"));
    if (path.isEmpty()) {
        return;
    }
    if (!m_dataManager->exportToTxt(path)) {
        QMessageBox::warning(this, tr("Export Failed"), tr("Unable to save the history export file."));
        return;
    }
    QMessageBox::information(this, tr("Exported"), tr("History has been exported successfully."));
}

void HistoryWindow::updateList()
{
    m_listWidget->clear();
    for (const Record &record : m_filteredRecords) {
        const QString title = QString("[%1] %2 - %3").arg(record.timestamp.toString(Qt::ISODate), record.mood, record.type);
        auto *item = new QListWidgetItem(title, m_listWidget);
        item->setData(Qt::UserRole, record.id);
        item->setToolTip(record.content);
    }
}

Record HistoryWindow::findRecord(const QString &recordId) const
{
    const auto list = m_dataManager->allRecords();
    for (const Record &record : list) {
        if (record.id == recordId) {
            return record;
        }
    }
    return Record();
}

void HistoryWindow::showRecordDetail(const Record &record)
{
    if (record.id.isEmpty()) {
        return;
    }

    const QString detail = QString("%1\n%2\n%3\n\n%4")
        .arg(record.timestamp.toString(Qt::ISODate), record.mood, record.type, record.content);

    QMessageBox msgBox(this);
    msgBox.setWindowTitle(tr("Record Detail"));
    msgBox.setText(detail);
    auto *editButton = msgBox.addButton(tr("Edit"), QMessageBox::AcceptRole);
    auto *deleteButton = msgBox.addButton(tr("Delete"), QMessageBox::DestructiveRole);
    msgBox.addButton(tr("Close"), QMessageBox::RejectRole);
    msgBox.exec();

    if (msgBox.clickedButton() == editButton) {
        const QString newContent = QInputDialog::getMultiLineText(this, tr("Edit Record"), tr("Content:"), record.content);
        if (!newContent.isEmpty()) {
            Record edited = record;
            edited.content = newContent;
            m_dataManager->updateRecord(edited);
            refreshRecords();
        }
    } else if (msgBox.clickedButton() == deleteButton) {
        const auto result = QMessageBox::question(this, tr("Delete Record"), tr("Delete this record permanently?"));
        if (result == QMessageBox::Yes) {
            m_dataManager->removeRecord(record.id);
            refreshRecords();
        }
    }
}
