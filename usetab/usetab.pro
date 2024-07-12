QT       += core gui sql
QT       += multimedia
QT       += core


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arrengpage.cpp \
    board.cpp \
    choosmode.cpp \
    choosreg.cpp \
    clicked.cpp \
    companypage.cpp \
    dragwidget.cpp \
    loading.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    ship.cpp \
    signup.cpp \
    withfriend.cpp \
    withrbot.cpp

HEADERS += \
    arrengpage.h \
    board.h \
    choosmode.h \
    choosreg.h \
    clicked.h \
    companypage.h \
    dragwidget.h \
    loading.h \
    login.h \
    mainwindow.h \
    ship.h \
    signup.h \
    withfriend.h \
    withrbot.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
