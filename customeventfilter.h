#ifndef CUSTOMEVENTFILTER_H
#define CUSTOMEVENTFILTER_H

#include <QObject>
#include <QTimer>
#include <QString>
#include <QFile>

class CustomEventFilter : public QObject
{
    Q_OBJECT
public:
    explicit CustomEventFilter(QObject *parent = 0);
    bool eventFilter(QObject *obj, QEvent *ev);
    QTimer inactivityTimer;
    bool isSleeping;
    int lastBrightness;
    void adjustBrightness(int brightness);
    void debug(QString message);

signals:

public slots:
    void goToSleep();

};

#endif // CUSTOMEVENTFILTER_H
