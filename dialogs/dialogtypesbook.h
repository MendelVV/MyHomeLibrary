#ifndef DIALOGTYPESBOOK_H
#define DIALOGTYPESBOOK_H

#include "layouttoform.h"
#include "database/sqlclass.h"
#include "dialogs/dialoginform.h"

class DialogTypesBook : public QDialog
{
    Q_OBJECT
public:
    explicit DialogTypesBook(SQLClass* dbC, QWidget *parent = 0);
    ~DialogTypesBook();
protected:
    FormPlusData* form;
    SQLClass* db;
    QListWidget* listW;
signals:

public slots:
    void slotAdd();
    void slotRemove();
    void slotAccept();
};

#endif // DIALOGTYPESBOOK_H
