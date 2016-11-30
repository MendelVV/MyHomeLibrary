#ifndef DATEEDITCELL_H
#define DATEEDITCELL_H

#include <QtWidgets>
#include <QDate>
#include <QKeyEvent>
#include "cellplusclass.h"
#include "lineeditcell.h"

class D_FORM DateEditCell : public LineEditCell
{
    Q_OBJECT
public:
    DateEditCell(CellClass* cell, QWidget *parent = 0);
    DateEditCell(CellPlusClass* cell, QWidget *parent = 0);
protected:

signals:

public slots:

};

#endif // DATEEDITCELL_H
