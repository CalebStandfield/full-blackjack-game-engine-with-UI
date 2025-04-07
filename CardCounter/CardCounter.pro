QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bettingview.cpp \
    card.cpp \
    controller.cpp \
    deck.cpp \
    gamestate.cpp \
    hand.cpp \
    main.cpp \
    mainwindow.cpp \
    statistics.cpp \
    statsview.cpp \
    tableview.cpp

HEADERS += \
    bettingview.h \
    card.h \
    controller.h \
    deck.h \
    gamestate.h \
    hand.h \
    mainwindow.h \
    statistics.h \
    statsview.h \
    tableview.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Playing Cards/3_of_clubs.png

RESOURCES += \
    CardsPNGFolder.qrc
