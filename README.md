###  InactivityTimer — Sleep/Wake Event Filter Implementation
---

Application level sleep/wake implementation through [event filter](http://doc.qt.io/qt-5/eventsandfilters.html) in Qt EGLFS. 

This timer is used for dimming or blanking the screen on Qt EGLFS application when there is no keyboard or mouse activity for a period of time. Once keyboard or mouse is pressed. the screen will then wake up to the full brightness.

This timer make use of QEvent::KeyPress and QEvent::MouseMove hooks and waits for the hooks to trigger and adjust the screen brightness by writing a value (0 to 255) to **/sys/class/backlight/rpi_backlight/brightness**. It is used to replace system level screen saver/screen blanking on Raspbian, which doesn't work if the Qt application run directly on top of [EGLFS](http://doc.qt.io/qt-5/embedded-linux.html).

The 4 variables in this timer are:

```c++
filter.setDebug(false);
filter.setTimeOut(60000); // microseconds before inactivity kicks in, defaults to 1 minute
filter.setMinBrightness(12); // 7" official touchscreen brightness (0 to 255), higher is brighter
filter.setMaxBrightness(200);
```

To use this sleep/wake event filter in your Qt application, drop in [customeventfilter.h](customeventfilter.h) and [customeventfilter.cpp](customeventfilter.cpp) to your project, include the header in your main.cpp and install the filter to the instance of QApplication:

```c++
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
    filter.setTimeOut(60000);
    filter.setMinBrightness(12);
    filter.setMaxBrightness(200);
    a.installEventFilter(&filter);

    return a.exec();
}

```

#### Tested on
---
- Raspbian Jessie Lite
- Raspberry Pi 2 Model B
- Official 7" Touchscreen