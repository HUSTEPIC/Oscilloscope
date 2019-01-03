QT += widgets serialport charts printsupport qml
requires(qtConfig(combobox))

# makefile format
TEMPLATE = app
TARGET = Oscilloscope
INCLUDEPATH =

SOURCES += \
    src/console.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/oscilloscope.cpp \
    src/qcustomplot.cpp \
    src/settingsdialog.cpp

HEADERS += \
    src/console.h \
    src/mainwindow.h \
    src/oscilloscope.h \
    src/qcustomplot.h \
    src/settingsdialog.h

FORMS += \
    res/mainwindow.ui \
    res/settingsdialog.ui

RESOURCES += \
    res/Oscilloscope.qrc

CONFIG(debug, debug|release) {#debug
        MYDIR = $$PWD/build/debug
        DESTDIR = .
        OBJECTS_DIR = $$MYDIR
        MOC_DIR = $$MYDIR
        RCC_DIR = $$MYDIR
        UI_DIR = $$MYDIR
    } else {#release
        MYDIR = $$PWD/build/release
        DESTDIR = .
        OBJECTS_DIR = $$MYDIR           # *.obj
        MOC_DIR = $$MYDIR               # moc_*.cpp
        RCC_DIR = $$MYDIR               # qrc_*.cpp
        UI_DIR = $$MYDIR                # ui_*.h
    }

