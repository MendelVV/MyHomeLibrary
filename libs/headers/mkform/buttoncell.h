#ifndef BUTTONCELL_H
#define BUTTONCELL_H

#include "cellplusclass.h"
#include <QtWidgets>

class D_FORM ButtonCell : public QPushButton
{
    Q_OBJECT
public:
    explicit ButtonCell(CellClass* cell, QWidget *parent = 0);
    explicit ButtonCell(CellPlusClass* cell, QWidget *parent = 0);
    CellClass* getCellBase();
    CellPlusClass* getCellPlusBase();
protected:
    CellClass* cellBase;//ячейка на основе которой формируем виджеты
    CellPlusClass* cellPlusBase;
    bool event(QEvent *e);
    void keyPressEvent(QKeyEvent* e);
signals:
    void keyMove(int,int);
    void signalTab();
public slots:
    void slotChangeFromCell();
    void slotPress();
};

#endif // BUTTONCELL_H
