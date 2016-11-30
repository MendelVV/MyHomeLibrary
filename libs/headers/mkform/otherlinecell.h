#ifndef OTHERLINECELL_H
#define OTHERLINECELL_H

#include "lineeditcell.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <QValidator>

class D_FORM OtherLineCell : public LineEditCell
{
Q_OBJECT
public:
    OtherLineCell(CellClass* cell, QWidget *parent = 0);
    OtherLineCell(CellPlusClass* cell, QWidget *parent = 0);
signals:
public slots:
};

#endif // OTHERLINECELL_H
