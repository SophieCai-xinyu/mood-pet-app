#ifndef INPUTWINDOW_H
#define INPUTWINDOW_H

#include <QWidget>
#include <QColor>

struct Record;

class QLabel;
class QLineEdit;
class QTextEdit;
class QPushButton;
class QComboBox;
class QMouseEvent;
class QEvent;
class QString;
class QFont;

class InputWindow : public QWidget
{
    Q_OBJECT

public:
    explicit InputWindow(QWidget *parent = nullptr);
    ~InputWindow() override;

    void showInputWindow();
    void hideInputWindow();
    void setTextColor(const QColor &color);
    void setTextFont(const QFont &font);

signals:
    void recordSaved(const Record &record);
    void windowShowed();
    void windowHided();

private slots:
    void onSaveClicked();
    void onClearClicked();
    void onMoodChanged(int index);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    void createLayout();
    void loadStyleSheet();
    void clearInputs();
    void applyTextStyle();

    QPoint m_dragPosition;
    QLabel *m_titleLabel;
    QTextEdit *m_noteInput;
    QComboBox *m_moodBox;
    QPushButton *m_saveButton;
    QPushButton *m_clearButton;
    QPushButton *m_hideButton;
    QString m_currentMood;
    QColor m_textColor;
    QFont m_textFont;
};

#endif // INPUTWINDOW_H
