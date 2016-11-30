#ifndef LISTCELL_H
#define LISTCELL_H

#include <QtWidgets>
#include "cellplusclass.h"

class D_FORM ListCell : public QListWidget
{
    Q_OBJECT
public:
    explicit ListCell(CellClass* cell, QWidget *parent = 0);
    explicit ListCell(CellPlusClass* cell, QWidget *parent = 0);
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
    void slotChangeValue(QListWidgetItem*);
};

#endif // LISTCELL_H
