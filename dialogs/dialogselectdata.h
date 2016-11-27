#ifndef DIALOGSELECTDATA_H
#define DIALOGSELECTDATA_H

#include <QtWidgets>
#include "sqlclass.h"

class DialogSelectData : public QDialog
{
    Q_OBJECT
public:
    explicit DialogSelectData(QString columnName, SQLClass* dbC, QVector<QString> vals, QWidget *parent = 0);
protected:
    double x;
    double y;
    SQLClass* db;
    QLineEdit* text;
    QPushButton* butAdd;
    QListWidget* lwgt;

    QVector<QString> vecVal;
signals:

public slots:
    void slotAddValue();
};

#endif // DIALOGSELECTDATA_H
