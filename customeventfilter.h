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

    bool DEBUG;
    int TIMEOUT;
    int MIN_BRIGHTNESS;
    int MAX_BRIGHTNESS;

    QTimer inactivityTimer;
    bool isSleeping;
    int lastBrightness;

    void setTimeOut(int microseconds);
    void setMinBrightness(int brightness);
    void setMaxBrightness(int brightness);
    void setDebug(bool status);
    void adjustBrightness(int brightness);
    void commitBrightness(int brightness);
    void debug(QString message);

public slots:
    void goToSleep();

};
#endif // CUSTOMEVENTFILTER_H
