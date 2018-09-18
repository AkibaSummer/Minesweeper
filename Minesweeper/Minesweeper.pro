#-------------------------------------------------
#
# Project created by QtCreator 2018-09-15T11:47:30
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = Minesweeper
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
CONFIG += resources_big
SOURCES += \
        main.cpp \
        Minesweeper.cpp \
        game.cpp \
    rule.cpp \
    custom.cpp

HEADERS += \
        Minesweeper.h \
        game.h \
    rule.h \
    stdc++.h \
    custom.h

FORMS += \
        Minesweeper.ui \
    rule.ui \
    custom.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res_1.qrc \
    res_2.qrc \
    res_3.qrc \
    res_4.qrc \
    custompic.qrc

DISTFILES +=
