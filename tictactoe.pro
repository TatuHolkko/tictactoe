TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    game/game.cpp \
    game/cell.cpp \
    game/gridhelper.cpp

HEADERS += \
    game/game.h \
    game/cell.h
