#ifndef TEXTEDITCELL_H
#define TEXTEDITCELL_H

#include <QtWidgets>
#include <QKeyEvent>
#include "cellplusclass.h"

class D_FORM TextEditCell : public QTextEdit
{
    Q_OBJECT
public:
    TextEditCell(CellClass* cell, QWidget *parent = 0);
    TextEditCell(CellPlusClass* cell, QWidget *parent = 0);
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

#endif // TEXTEDITCELL_H
