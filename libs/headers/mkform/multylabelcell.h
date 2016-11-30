#ifndef MULTYLABELCELL_H
#define MULTYLABELCELL_H

#include <QtWidgets>
#include <QKeyEvent>
#include "cellclass.h"
#include "texteditcell.h"

class D_FORM MultyLabelCell : public TextEditCell
{
    Q_OBJECT
public:
    explicit MultyLabelCell(CellClass* cell, QWidget *parent = 0);
    explicit MultyLabelCell(CellPlusClass* cell, QWidget *parent = 0);
protected:
    void keyPressEvent(QKeyEvent* e);

signals:
public slots:
};

#endif // MULTYLABELCELL_H
