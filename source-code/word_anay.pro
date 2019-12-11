#-------------------------------------------------
#
# Project created by QtCreator 2019-09-18T14:34:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = word_anay
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    word.cpp \
    grammer.cpp \
    treewindow.cpp \
    treenode.cpp \
    treemainwindow.cpp \
    order.cpp \
    exer.cpp \
    identify.cpp \
    id_table.cpp \
    inputdialog.cpp

HEADERS += \
        mainwindow.h \
    word.h \
    grammer.h \
    treewindow.h \
    treenode.h \
    treemainwindow.h \
    order.h \
    exer.h \
    identify.h \
    id_table.h \
    inputdialog.h

FORMS += \
        mainwindow.ui \
    treewindow.ui \
    treemainwindow.ui \
    inputdialog.ui

RESOURCES += \
    res.qrc
