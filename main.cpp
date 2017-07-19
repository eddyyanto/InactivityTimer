#include "mainwindow.h"
#include <QApplication>
#include <customeventfilter.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    CustomEventFilter filter;
    filter.setDebug(false);
    filter.setTimeOut(5000);
    filter.setMinBrightness(12);
    filter.setMaxBrightness(200);
    a.installEventFilter(&filter);

    return a.exec();
}
