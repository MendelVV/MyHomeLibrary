#ifndef LABELCELL_H
#define LABELCELL_H

#include "lineeditcell.h"

class D_FORM LabelCell : public LineEditCell
{
    Q_OBJECT
public:
    LabelCell(CellClass* cell, QWidget *parent = 0);
    LabelCell(CellPlusClass* cell, QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent* e);
    void mouseDoubleClickEvent(QMouseEvent *event);
signals:

public slots:

};

#endif // LABELCELL_H
