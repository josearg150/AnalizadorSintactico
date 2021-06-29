QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
RC_ICONS = icon.ico

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    generararchivo.cpp \
    mainwindow.cpp \
    analisislexico.cpp \
    analisissintactico.cpp \
    archivo.cpp \
    pila.cpp \
    secundario.cpp

HEADERS += \
    generararchivo.h \
    mainwindow.h \
    analisislexico.h \
    analisissintactico.h \
    archivo.h \
    pila.h

FORMS += \
    generararchivo.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
