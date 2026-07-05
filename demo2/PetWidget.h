#ifndef PETWIDGET_H
#define PETWIDGET_H

#include <QWidget>
#include <QVector>
#include <QString>
#include <QDateTime>

class QLabel;
class QMovie;
class QTimer;

struct AlarmNote {
    QString content;
    QDateTime targetTime;
    bool isTriggered = false;
};

class PetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PetWidget(QWidget *parent = nullptr);
    ~PetWidget() override;

    void setMood(const QString &mood);
    void setStateIdle();
    void setStateNormal();
    void setStateRecording();
    void setStateSuccess();

signals:
    void petClicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

private:
    void showBubble();
    bool loadLocalMovie(const QString &filename);

    QPoint m_dragPosition;
    QString m_mood;
    QLabel *m_display;
    QMovie *m_movie;
    QVector<QString> m_gifs;
    QLabel *m_bubble;
    QTimer *m_bubbleTimer;
    QTimer *m_clockTimer;
    QVector<AlarmNote> m_alarms;
    void checkAlarms();
};

#endif // PETWIDGET_H
