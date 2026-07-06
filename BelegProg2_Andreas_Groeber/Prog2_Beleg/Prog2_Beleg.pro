
#Name:Andreas Gröber
#Matr.Nr.:47708
#Studiengruppe:19/041/01
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    add_item.cpp \
    add_person.cpp \
    buch.cpp \
    cd.cpp \
    delete_item.cpp \
    delete_person.cpp \
    item.cpp \
    main.cpp \
    mainwindow.cpp \
    person.cpp \
    view_item.cpp \
    view_person.cpp

HEADERS += \
    add_item.h \
    add_person.h \
    buch.h \
    cd.h \
    delete_item.h \
    delete_person.h \
    item.h \
    mainwindow.h \
    person.h \
    view_item.h \
    view_person.h

FORMS += \
    add_item.ui \
    add_person.ui \
    delete_item.ui \
    delete_person.ui \
    mainwindow.ui \
    view_item.ui \
    view_person.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    listen/Itemlist.csv
