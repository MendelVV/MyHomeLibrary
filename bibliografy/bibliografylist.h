#ifndef BIBLIOGRAFYLIST_H
#define BIBLIOGRAFYLIST_H

#include <QtWidgets>
#include "database/sqlclass.h"
#include "bibliografytable.h"
#include "bibliografywindow.h"

class BibliografyList : public QMainWindow
{
    Q_OBJECT
public:
    explicit BibliografyList(SQLClass* dbC, QWidget *parent = 0);//список всех вариантов оформления списка литературы
protected:
    double x;
    double y;
    SQLClass* db;
    BibliografyTable* table;

    QAction* actAdd;
    QAction* actSave;
    QAction* actSaveAndClose;
    QAction* actClose;
    void setActMenu();
signals:

public slots:
    void slotAdd();
    void slotAddInDb(BibliografyClass*);
    void slotEditInDb(BibliografyClass*);//если отредактировали
    void slotOpen(QString code);
    void slotRemove(QString);
    void slotSave();
    void slotSaveAndClose();
};

#endif // BIBLIOGRAFYLIST_H
