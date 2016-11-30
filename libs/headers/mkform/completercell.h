#ifndef COMPLETERCELL_H
#define COMPLETERCELL_H

#include "lineeditcell.h"
#include <QCompleter>

class D_FORM CompleterCell: public LineEditCell
{
    Q_OBJECT
public:
    CompleterCell(CellClass* cell, QWidget *parent = 0);
    CompleterCell(CellPlusClass* cell, QWidget *parent = 0);
protected:
signals:
public slots:
    void slotEditList();
};

#endif // COMPLETERCELL_H
