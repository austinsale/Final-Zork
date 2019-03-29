TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    item.cpp \
    container.cpp \
    creature.cpp \
    room.cpp \
    inventory.cpp \
    parser.cpp \
    trigger.cpp \
    condition.cpp \
    hcondition.cpp \
    scondition.cpp \
    ccondition.cpp \
    GameHandler.cpp

HEADERS += \
    item.h \
    container.h \
    creature.h \
    room.h \
    inventory.h \
    rapidxml.hpp \
    parser.h \
    trigger.h \
    condition.h \
    hcondition.h \
    scondition.h \
    ccondition.h \
    GameHandler.h
