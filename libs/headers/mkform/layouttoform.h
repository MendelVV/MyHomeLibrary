#ifndef LAYOUTTOFORM_H
#define LAYOUTTOFORM_H

#include <QGridLayout>
#include <QtWidgets>
#include "cellclass.h"
#include "formdata.h"
#include "formplusdata.h"
#include "widgetscells.h"

class D_FORM LayoutToForm : public QGridLayout
{
    Q_OBJECT
public:
    explicit LayoutToForm();
    void addFormData(FormData*);
    void addFormData(FormPlusData*);
    FormData* getForm();
protected:
    FormData* form;
    FormPlusData* formPlus;
    //ее мы сохраняем на конечной машине и используем в качестве основной для заполнения данных
    void addCell(CellClass*);
    void addCell(CellPlusClass*);
signals:
    void changeCell(QString s);
    void signalMoved();
public slots:
    void slotKeyMove(int, int);
    void slotChangeCell(QString s);
    void slotTab();
};

#endif // LAYOUTTOFORM_H
