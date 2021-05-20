QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    mainwindowguest.cpp \
    mainwindowsailer.cpp \
    management.cpp \
    managementdetail.cpp \
    money_buyer.cpp \
    money_sailer.cpp \
    new_project.cpp \
    projectpreview.cpp \
    register.cpp \
    shopdetail_buyer.cpp \
    shopdetail_sailer.cpp \
    shopmall.cpp \
    shopmall_sailer.cpp \
    sqilteopreatorprojects.cpp \
    sqliteoperator.cpp \
    username_buyer.cpp \
    username_sailer.cpp \
    widget.cpp

HEADERS += \
    Classes.h \
    mainwindow.h \
    mainwindowguest.h \
    mainwindowsailer.h \
    management.h \
    managementdetail.h \
    money_buyer.h \
    money_sailer.h \
    new_project.h \
    projectpreview.h \
    register.h \
    shopdetail_buyer.h \
    shopdetail_sailer.h \
    shopmall.h \
    shopmall_sailer.h \
    sqilteopreatorprojects.h \
    sqliteoperator.h \
    username_buyer.h \
    username_sailer.h \
    widget.h

FORMS += \
    mainwindow.ui \
    mainwindowguest.ui \
    mainwindowsailer.ui \
    management.ui \
    managementdetail.ui \
    money_buyer.ui \
    money_sailer.ui \
    new_project.ui \
    projectpreview.ui \
    register.ui \
    shopdetail_buyer.ui \
    shopdetail_sailer.ui \
    shopmall.ui \
    shopmall_sailer.ui \
    username_buyer.ui \
    username_sailer.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pictures.qrc
