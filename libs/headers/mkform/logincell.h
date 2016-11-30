#ifndef LOGINCELL_H
#define LOGINCELL_H

#include "lineeditcell.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <QValidator>

class D_FORM LoginCell : public LineEditCell
{
Q_OBJECT
public:
    LoginCell(CellClass* cell, QWidget *parent = 0);
    LoginCell(CellPlusClass* cell, QWidget *parent = 0);
};

#endif // LOGINCELL_H
