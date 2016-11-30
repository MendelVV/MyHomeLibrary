#-------------------------------------------------
#
# Project created by QtCreator 2016-03-08T16:55:03
#
#-------------------------------------------------

QT += core gui xml sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

VERSION = 1.1.0.1

RC_ICONS = lib.ico

TARGET = MyHomeLibrary
TEMPLATE = app

TRANSLATIONS +=myhomelibrary_ru.ts

DEPENDPATH+=libs/headers/mkform
INCLUDEPATH+=libs/headers/mkform

LIBS+=-LC:/Qt/projects/MyHomeLibrary/libs -lmkform1

SOURCES += main.cpp \
    dialogs/dialogcreatelibrary.cpp \
    dialogs/bookview.cpp \
    dialogs/dialogselectdata.cpp \
    styleclass.cpp \
    dialogs/dialogtypesbook.cpp \
    dialogs/dialoginform.cpp \
    bibliografy/bibliografyclass.cpp \
    bibliografy/bibliografyitem.cpp \
    bibliografy/bibliografyview.cpp \
    bibliografy/bibliografywindow.cpp \
    bibliografy/bibliografylist.cpp \
    bibliografy/bibliografytable.cpp \
    dialogs/dialogselectlibrary.cpp \
    widgets/filterwidget.cpp \
    widgets/bookstable.cpp \
    widgets/searchwidget.cpp \
    widgets/librarywindow.cpp \
    library_classes/bookclass.cpp \
    library_classes/libraryclass.cpp \
    library_classes/settingsbooksclass.cpp \
    database/sqlclass.cpp \
    database/sqlcursor.cpp

HEADERS  += \
    dialogs/dialogcreatelibrary.h \
    dialogs/bookview.h \
    dialogs/dialogselectdata.h \
    styleclass.h \
    dialogs/dialogtypesbook.h \
    dialogs/dialoginform.h \
    bibliografy/bibliografyclass.h \
    bibliografy/bibliografyitem.h \
    bibliografy/bibliografyview.h \
    bibliografy/bibliografywindow.h \
    bibliografy/bibliografylist.h \
    bibliografy/bibliografytable.h \
    dialogs/dialogselectlibrary.h \
    widgets/filterwidget.h \
    widgets/bookstable.h \
    widgets/librarywindow.h \
    widgets/searchwidget.h \
    library_classes/bookclass.h \
    library_classes/settingsbooksclass.h \
    library_classes/libraryclass.h \
    database/sqlclass.h \
    database/sqlcursor.h

RESOURCES += \
    resource.qrc

FORMS +=

