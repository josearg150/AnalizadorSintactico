TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    analisislexico.cpp \
    analisissintactico.cpp \
    analizador.cpp \
    archivo.cpp \
    pila.cpp

HEADERS += \
    analisislexico.h \
    analisissintactico.h \
    analizador.h \
    archivo.h \
    pila.h
