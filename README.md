###  InactivityTimer — Qt Custom Event Filter

App level inactivity timer implementation through [event filter](http://doc.qt.io/qt-5/eventsandfilters.html) in Qt EGLFS. Once the event filter detects inactivity (no key/mouse movement), it will dim the screen. This is to replace Raspbian system level screen saver/screen blanking, which by experience doesn't work if the Qt app runs on top of EGLFS.

The 3 variables that can adjusted are below:

```c++
const int TIMEOUT           = 60000; // microseconds before inactivity kicks in
const int MIN_BRIGHTNESS    = 12; // 7" touchscreen brightness 0-255
const int MAX_BRIGHTNESS    = 200;
```

To use this event filter, drop in [customeventfilter.h](customeventfilter.h) and [customeventfilter.cpp](customeventfilter.cpp) and include it in your main entry:

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
    a.installEventFilter(&filter);

    return a.exec();
}
```
