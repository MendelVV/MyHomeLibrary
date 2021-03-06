#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include "layouttoform.h"
#include "database/sqlclass.h"

class SearchWidget : public QDialog
{
    Q_OBJECT
public:
    explicit SearchWidget(SQLClass* dbC, QWidget *parent = 0);
    ~SearchWidget();
    FormPlusData* form;
    SQLClass* db;
    QVector<QVector<QString> > result;
protected:
    void setFormText();
signals:

public slots:
    void slotRefresh();
    void slotSearch();
};

#endif // SEARCHWIDGET_H
