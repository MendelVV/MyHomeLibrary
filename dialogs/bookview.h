#ifndef BOOKVIEW_H
#define BOOKVIEW_H

#include "layouttoform.h"
#include "library_classes/bookclass.h"
#include "database/sqlclass.h"
#include "library_classes/settingsbooksclass.h"

class BookView : public QMainWindow
{
    Q_OBJECT
public:
    explicit BookView(BookClass* bk, SQLClass* dbC, SettingsBooksClass* set, QWidget *parent = 0);
    ~BookView();

protected:
    bool isNew;
    QString oldCode;
    FormPlusData* form;
    BookClass* book;
    SQLClass* db;
    SettingsBooksClass* setting;

    QAction* actSave;
    QAction* actSaveAndClose;
    QAction* actClose;
    QAction* actOpenBook;
    QAction* actSelectFile;
    void setActMenu();
    void setFormText();
signals:
    void signalNew(BookClass*);
    void signalSave(BookClass*,QString);
public slots:
    void slotSave();
    void slotSaveAndClose();
    void slotSelectFile();
    void slotOpenBook();

    void slotPlusValue();
    void slotMinusValue();
};

#endif // BOOKVIEW_H
