#ifndef SCROLLWIDGET_H
#define SCROLLWIDGET_H

#include "layouttoform.h"

class D_FORM ScrollWidget : public QScrollArea
{
    Q_OBJECT
public:
    explicit ScrollWidget(LayoutToForm* layout, QWidget *parent = 0);

signals:

public slots:
    void slotSetVisible();
};

#endif // SCROLLWIDGET_H
