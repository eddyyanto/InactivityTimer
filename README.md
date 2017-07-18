###  InactivityTimer — Qt Custom Event Filter Implementation 

Application level inactivity/sleep timer implementation through [event filter](http://doc.qt.io/qt-5/eventsandfilters.html) in Qt EGLFS. 

This timer is used to dim/blank the screen on Qt EGLFS application once the filter detects no key/mouse movement for a period of time. The dimming/blanking was done through writing a value within a range of 0 to 255 to **/sys/class/backlight/rpi_backlight/brightness**.

This timer used is to replace system level screen saver/screen blanking on Raspbian, which doesn't work if the Qt application directly run on top of [EGLFS](http://doc.qt.io/qt-5/embedded-linux.html).

The 3 variables (in customeventfilter.cpp) that can adjusted are below:

```c++
const int TIMEOUT           = 60000; // microseconds before inactivity kicks in
const int MIN_BRIGHTNESS    = 12; // 7" touchscreen brightness within a range of 0 to 255, higher is brighter
const int MAX_BRIGHTNESS    = 200;
```

To use this event filter, drop in [customeventfilter.h](customeventfilter.h) and [customeventfilter.cpp](customeventfilter.cpp) to your project. And include the header in your main.cpp:

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

#### Tested on
- Raspbian Jessie Lite
- Raspberry Pi 2 Model B
- Official 7" Touchscreen
