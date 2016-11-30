#ifndef CHECKBOXCELL_H
#define CHECKBOXCELL_H

#include "cellplusclass.h"
#include <QtWidgets>

class D_FORM CheckBoxCell : public QCheckBox
{
    Q_OBJECT
public:
    explicit CheckBoxCell(CellClass* cell, QWidget *parent = 0);
    explicit CheckBoxCell(CellPlusClass* cell, QWidget *parent = 0);
    CellClass* getCellBase();
    CellPlusClass* getCellPlusBase();
protected:
    CellClass* cellBase;//ячейка на основе которой формируем виджеты
    CellPlusClass* cellPlusBase;//ячейка на основе которой формируем виджеты
    bool event(QEvent *e);
    void keyPressEvent(QKeyEvent* e);

signals:
    void keyMove(int,int);
    void signalTab();
public slots:
    void slotChangeFromCell();
};

#endif // CHECKBOXCELL_H
