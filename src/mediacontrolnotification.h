#ifndef MEDIACONTROLNOTIFICATION_H
#define MEDIACONTROLNOTIFICATION_H

#include <QObject>

class MediaControlNotification : public QObject
{
    Q_OBJECT
public:
    explicit MediaControlNotification(QObject *parent = nullptr);
    static MediaControlNotification *instance() { return m_instance; }
    Q_INVOKABLE void notificate(QString string);

signals:
    void onNotificationUpdate(QString string);
    void playButtonClicked();
    void nextButtonClicked();
    void previousButtonClicked();

private slots:
    void showNotification(QString string);

private:
    static MediaControlNotification *m_instance;
};

#endif // MEDIACONTROLNOTIFICATION_H
