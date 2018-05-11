TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    asset.cpp \
    computer.cpp \
    date.cpp \
    menuinterface.cpp \
    assetregister.cpp

HEADERS += asset.h \
    computer.h \
    date.h \
    menuinterface.h \
    assetregister.h
