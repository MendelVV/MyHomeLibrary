#ifndef LIBRARYWIMDOW_H
#define LIBRARYWIMDOW_H

#include <QtWidgets>
#include <QCoreApplication>
#include "bookstable.h"
#include "database/sqlclass.h"
#include "library_classes/libraryclass.h"
#include "dialogs/dialogcreatelibrary.h"
#include "dialogs/bookview.h"
#include "dialogs/dialogtypesbook.h"
#include "widgets/filterwidget.h"
#include "bibliografy/bibliografylist.h"
#include "dialogs/dialoginform.h"
#include "dialogs/dialogselectlibrary.h"
#include "searchwidget.h"

class LibraryWindow : public QMainWindow//главный класс интерфейса
{
    Q_OBJECT
public:

    explicit LibraryWindow(QWidget *parent = 0);
protected:
    double x;
    double y;
    BooksTable* tableBooks;
    FilterWidget* filter;
    QVector<QVector<QString> > data;
    LibraryClass* lib;
    void readData();
    SQLClass* db;
    FormPlusData* formInf;

    QAction* actSelect;
    QAction* actSave;
    QAction* actExit;

    QAction* actLoadXml;
    QAction* actExportXml;
    QAction* actAddBook;
    QAction* actSearch;
    QAction* actRemoveBook;

    QAction* actTypesPublication;
    QAction* actBibliographiType;

    QAction* actBibliographiList;
    QAction* actAbout;

    void setActMenu();
    QToolBar* createToolBar();

    BookClass* readBook(QString code);
signals:

public slots:
    void slotSelect();
    void slotSave();
    void slotAddBook();
    void slotSearch();
    void slotRemoveBook();
    void slotLoadXML();
    void slotExportXML();
    void slotCreateLibrary();
    void slotTypesPublication();
    void slotSelectedCount(int);
    void slotBibliografyType();
    void slotBibliografyList();

    void slotNewBook(BookClass*);//добавляем новую книгу в базу данных и дирректорию
    void slotSaveBook(BookClass*,QString);//сохраняем книгу
    void slotOpenBook(QString code);
    void slotOpenBookFile(QString code);

    void slotAbout();
};

#endif // LIBRARYWIMDOW_H
