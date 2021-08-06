QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
                                  QT += sql

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    inforofman.cpp \
    isolatedplace.cpp \
    main.cpp \
    mysql.cpp \
    sqlite3.c \
    mainmenu.cpp \
    mainwindow.cpp \
    tableview.cpp

HEADERS += \
    inforofman.h \
    isolatedplace.h \
    mysql.h \
    sqlite3.h \
    mainmenu.h \
    mainwindow.h \
    tableview.h

FORMS += \
    mainmenu.ui \
    mainwindow.ui \
    tableview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ImgResource.qrc
