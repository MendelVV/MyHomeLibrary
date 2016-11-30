#ifndef TABLEFORMDATA_H
#define TABLEFORMDATA_H

#include <QtWidgets>
#include "formdata.h"

class D_FORM TableFormData : public QTableWidget
{
    Q_OBJECT
public:
    explicit TableFormData(FormData* form, QWidget *parent = 0);
protected:
    QVector<int> vecRows;
    QVector<int> vecColumns;
    virtual void keyPressEvent(QKeyEvent *event);
signals:

public slots:

};

#endif // TABLEFORMDATA_H
