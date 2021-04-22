#-------------------------------------------------
#
# Project created by QtCreator 2015-03-06T09:12:30
#
#-------------------------------------------------

CONFIG += c++17

QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lan
TEMPLATE = app


SOURCES += main.cpp\
        lan.cpp \
    listitems.cpp \
    userbox.cpp \
    edititem.cpp \
    addrbox.cpp \
    item.cpp \
    address.cpp \
    attribute.cpp \
    link.cpp \
    lcombobox.cpp \
    editattribute.cpp \
    selectattribute.cpp \
    selattr.cpp \
    listmovements.cpp \
    showhistory.cpp \
    search.cpp \
    lobject.cpp \
    wgrattr.cpp \
    grattr.cpp \
    editname.cpp \
    listattribute.cpp \
    attributedata.cpp \
    exportdata.cpp \
    listtickets.cpp \
    editticket.cpp \
    clearlineedit.cpp \
    itemmoves.cpp

HEADERS  += lan.h \
    listitems.h \
    userbox.h \
    edititem.h \
    addrbox.h \
    item.h \
    address.h \
    attribute.h \
    link.h \
    lcombobox.h \
    editattribute.h \
    selectattribute.h \
    selattr.h \
    listmovements.h \
    showhistory.h \
    search.h \
    lobject.h \
    wgrattr.h \
    grattr.h \
    editname.h \
    listattribute.h \
    attributedata.h \
    exportdata.h \
    listtickets.h \
    editticket.h \
    clearlineedit.h \
    itemmoves.h

FORMS    += lan.ui \
    listitems.ui \
    edititem.ui \
    editattribute.ui \
    selectattribute.ui \
    selattr.ui \
    listmovements.ui \
    showhistory.ui \
    search.ui \
    wgrattr.ui \
    editname.ui \
    listattribute.ui \
    listtickets.ui \
    editticket.ui
