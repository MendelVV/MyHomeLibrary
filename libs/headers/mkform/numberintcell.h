#ifndef NUMBERINTCELL_H
#define NUMBERINTCELL_H

#include "numbercell.h"

class D_FORM NumberIntCell : public NumberCell
{
    Q_OBJECT
public:
    explicit NumberIntCell(CellClass* cell, QWidget *parent = 0);
    explicit NumberIntCell(CellPlusClass* cell, QWidget *parent = 0);
signals:

public slots:

};

#endif // NUMBERINTCELL_H
