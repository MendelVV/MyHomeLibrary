#ifndef NUMBERCELL_H
#define NUMBERCELL_H

#include "lineeditcell.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <QValidator>
#include <QPalette>

class D_FORM NumberCell : public LineEditCell
{
    Q_OBJECT
public:
    NumberCell(CellClass* cell, QWidget *parent = 0);
    NumberCell(CellPlusClass* cell, QWidget *parent = 0);
protected:
signals:
public slots:

};

#endif // NUMBERCELL_H
