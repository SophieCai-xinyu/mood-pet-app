#ifndef PETWIDGET_H
#define PETWIDGET_H

#include <QWidget>
#include <QVector>
#include <QString>

class QLabel;
class QMovie;
class QTimer;

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

private:
    bool loadLocalMovie(const QString &filename);

    QPoint m_dragPosition;
    QString m_mood;
    QLabel *m_display;
    QMovie *m_movie;
    QVector<QString> m_gifs;
    QLabel *m_bubble;
    QTimer *m_bubbleTimer;
};

#endif // PETWIDGET_H
