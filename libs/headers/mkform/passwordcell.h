#ifndef PASSWORDCELL_H
#define PASSWORDCELL_H

#include "lineeditcell.h"

class D_FORM PasswordCell : public LineEditCell
{
    Q_OBJECT
public:
    explicit PasswordCell(CellClass* cell, QWidget *parent = 0);
    explicit PasswordCell(CellPlusClass* cell, QWidget *parent = 0);

signals:

public slots:

};

#endif // PASSWORDCELL_H
