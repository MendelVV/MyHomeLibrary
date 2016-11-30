#ifndef COMBOBOXCELL_H
#define COMBOBOXCELL_H

#include <QtWidgets>
#include <QKeyEvent>
#include "cellplusclass.h"

class D_FORM ComboBoxCell : public QComboBox
{
    Q_OBJECT
public:
    ComboBoxCell(CellClass* cell, QWidget *parent = 0);
    ComboBoxCell(CellPlusClass* cell, QWidget *parent = 0);
    CellClass* getCellBase();
    CellPlusClass* getCellPlusBase();
protected:
    CellClass* cellBase;//ячейка на основе которой формируем виджеты
    CellPlusClass* cellPlusBase;//ячейка на основе которой формируем виджеты
    bool event(QEvent *event);
    void keyPressEvent(QKeyEvent* e);

signals:
    void keyMove(int,int);
    void signalTab();
public slots:
    void slotChangeFromCell();
    void slotEditList();
};

#endif // COMBOBOXCELL_H
