#ifndef MEDIACONTROLNOTIFICATION_H
#define MEDIACONTROLNOTIFICATION_H

#include <QObject>

class MediaControlNotification : public QObject
{
    Q_OBJECT
public:
    explicit MediaControlNotification(QObject *parent = nullptr);

signals:

};

#endif // MEDIACONTROLNOTIFICATION_H
