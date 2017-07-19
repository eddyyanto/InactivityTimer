#include "customeventfilter.h"
#include <QEvent>
#include <QFile>
#include <QDebug>

const QString filename      = "/sys/class/backlight/rpi_backlight/brightness";
QFile file(filename);

CustomEventFilter::CustomEventFilter(QObject *parent) :
    QObject(parent)
{
    DEBUG           = false;
    TIMEOUT         = 60000;
    MIN_BRIGHTNESS  = 12;
    MAX_BRIGHTNESS  = 200;
    isSleeping      = false;
    lastBrightness  = MAX_BRIGHTNESS;
    inactivityTimer.setInterval(TIMEOUT);
    connect(&inactivityTimer,SIGNAL(timeout()),this,SLOT(goToSleep()));
    inactivityTimer.start();
}

bool CustomEventFilter::eventFilter(QObject *obj, QEvent *ev)
{
    if(ev->type() == QEvent::KeyPress || ev->type() == QEvent::MouseMove){
        isSleeping = false;
        inactivityTimer.stop();
        inactivityTimer.start();
        this->adjustBrightness(MAX_BRIGHTNESS);
    }
    return QObject::eventFilter(obj, ev);
}

void CustomEventFilter::goToSleep()
{
    isSleeping = true;
    this->adjustBrightness(MIN_BRIGHTNESS);
}

void CustomEventFilter::adjustBrightness(int brightness)
{
    if(isSleeping == true){
        if(brightness != lastBrightness){
            lastBrightness = MIN_BRIGHTNESS;
            this->commitBrightness(MIN_BRIGHTNESS);
            this->debug(QString("Sleep."));
        }
    }else if(isSleeping == false){
        if(brightness != lastBrightness){
            lastBrightness = MAX_BRIGHTNESS;
            this->commitBrightness(MAX_BRIGHTNESS);
            this->debug(QString("Wake up."));
        }
    }
}

void CustomEventFilter::commitBrightness(int brightness)
{
    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream stream( &file );
        stream << brightness << endl;
    }else{
        this->debug(QString("Unable to open file."));
    }
    file.close();
}

void CustomEventFilter::setTimeOut(int microseconds)
{
    this->TIMEOUT = microseconds;
    this->inactivityTimer.setInterval(this->TIMEOUT);
}

void CustomEventFilter::setMinBrightness(int brightness)
{
    if(brightness < 0 && brightness > 255){
        this->debug("Brightness out or range (0-255.");
        return;
    }
    this->MIN_BRIGHTNESS = brightness;
}

void CustomEventFilter::setMaxBrightness(int brightness)
{
    if(brightness < 0 && brightness > 255){
        this->debug("Brightness out or range (0-255.");
        return;
    }
    this->MAX_BRIGHTNESS = brightness;
}

void CustomEventFilter::setDebug(bool status)
{
    this->DEBUG = status;
}

void CustomEventFilter::debug(QString message)
{
    if(DEBUG){
        qDebug() << message;
    }
}
