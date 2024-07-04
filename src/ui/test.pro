QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



LIBS += libegif.a

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    gifRecorder.cpp \
    gl_window.cpp \
    gifRecorderThread.cpp \
    mainFunc.cpp \
    mainwindow.cpp


HEADERS += \
    gl_window.h \
    gifRecorder.h \
    gifRecorderThread.h \
    mainwindow.h






FORMS += mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
