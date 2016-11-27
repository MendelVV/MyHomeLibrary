#-------------------------------------------------
#
# Project created by QtCreator 2016-03-08T16:55:03
#
#-------------------------------------------------

QT += core gui xml sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

VERSION = 1.0.1.1

RC_ICONS = lib.ico

TARGET = MyHomeLibrary
TEMPLATE = app

DEPENDPATH+=D:/My_dll_library/headers/mkform
INCLUDEPATH+=D:/My_dll_library/headers/mkform

LIBS+=-LD:/My_dll_library/qt_5.5 -lmkform1
#LIBS+=-LF:/My_dll_library/32_2 -lmkform1

SOURCES += main.cpp \
    bookclass.cpp \
    settingsbooksclass.cpp \
    sqlclass.cpp \
    sqlcursor.cpp \
    librarywindow.cpp \
    libraryclass.cpp \
    bookstable.cpp \
    dialogs/dialogcreatelibrary.cpp \
    dialogs/bookview.cpp \
    dialogs/dialogselectdata.cpp \
    filterwidget.cpp \
    styleclass.cpp \
    dialogs/dialogtypesbook.cpp \
    dialogs/dialoginform.cpp \
    bibliografy/bibliografyclass.cpp \
    bibliografy/bibliografyitem.cpp \
    bibliografy/bibliografyview.cpp \
    bibliografy/bibliografywindow.cpp \
    bibliografy/bibliografylist.cpp \
    bibliografy/bibliografytable.cpp \
    searchwidget.cpp \
    dialogs/dialogselectlibrary.cpp

HEADERS  += \
    bookclass.h \
    settingsbooksclass.h \
    sqlclass.h \
    sqlcursor.h \
    librarywindow.h \
    libraryclass.h \
    bookstable.h \
    dialogs/dialogcreatelibrary.h \
    dialogs/bookview.h \
    dialogs/dialogselectdata.h \
    filterwidget.h \
    styleclass.h \
    dialogs/dialogtypesbook.h \
    dialogs/dialoginform.h \
    bibliografy/bibliografyclass.h \
    bibliografy/bibliografyitem.h \
    bibliografy/bibliografyview.h \
    bibliografy/bibliografywindow.h \
    bibliografy/bibliografylist.h \
    bibliografy/bibliografytable.h \
    searchwidget.h \
    dialogs/dialogselectlibrary.h

RESOURCES += \
    resource.qrc

FORMS +=

