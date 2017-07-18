#include "customeventfilter.h"
#include <QEvent>
#include <QFile>
#include <QDebug>

const bool DEBUG            = true;
const int TIMEOUT           = 60000;
const int MIN_BRIGHTNESS    = 12;
const int MAX_BRIGHTNESS    = 200;

#ifdef Q_PROCESSOR_ARM
const QString filename      = "/sys/class/backlight/rpi_backlight/brightness";
#endif

#ifdef Q_PROCESSOR_X86
const QString filename      = "C:/brightness.txt";
#endif

QFile file(filename);

CustomEventFilter::CustomEventFilter(QObject *parent) :
    QObject(parent)
{
    isSleeping = false;
    lastBrightness = MAX_BRIGHTNESS;
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
            if ( file.open(QIODevice::ReadWrite) )
            {
                QTextStream stream( &file );
                stream << MIN_BRIGHTNESS << endl;
            }else{
                this->debug(QString("Unable to open file."));
            }
            file.close();
            this->debug(QString("Sleep."));
        }
    }else if(isSleeping == false){
        if(brightness != lastBrightness){
            lastBrightness = MAX_BRIGHTNESS;
            if ( file.open(QIODevice::ReadWrite) )
            {
                QTextStream stream( &file );
                stream << MAX_BRIGHTNESS << endl;
            }else{
                this->debug(QString("Unable to open file."));
            }
            file.close();
            this->debug(QString("Wake up."));
        }
    }
}

void CustomEventFilter::debug(QString message)
{
    if(DEBUG){
        qDebug() << message;
    }
}
