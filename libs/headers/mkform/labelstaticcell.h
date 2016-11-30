#ifndef LABELSTATICCELL_H
#define LABELSTATICCELL_H

#include <QtWidgets>
#include <QPalette>
#include <QKeyEvent>
#include "cellplusclass.h"

class D_FORM LabelStaticCell : public QLabel
{
    Q_OBJECT
public:
    explicit LabelStaticCell(CellClass* cell, QWidget *parent = 0);
    explicit LabelStaticCell(CellPlusClass* cell, QWidget *parent = 0);
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

#endif // LABELSTATICCELL_H
