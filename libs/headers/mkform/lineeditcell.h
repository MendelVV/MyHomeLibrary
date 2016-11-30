#ifndef LINEEDITCELL_H
#define LINEEDITCELL_H

#include <QtWidgets>
#include <QPalette>
#include <QKeyEvent>
#include "cellplusclass.h"

class D_FORM LineEditCell : public QLineEdit
{
    Q_OBJECT
public:
    explicit LineEditCell(CellClass* cell, QWidget *parent = 0);
    explicit LineEditCell(CellPlusClass* cell, QWidget *parent = 0);
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
    void slotShiftEnter();
};

#endif // LINEEDITCELL_H
