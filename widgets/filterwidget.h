#ifndef FILTERWIDGET_H
#define FILTERWIDGET_H

#include "scrollwidget.h"
#include "database/sqlclass.h"
#include "bookstable.h"

class FilterWidget : public QMainWindow
{
    Q_OBJECT
public:
    explicit FilterWidget(SQLClass* dbC, BooksTable* tab, QWidget *parent = 0);
protected:
    FormPlusData* form;
    BooksTable* table;
    SQLClass* db;

    void setFormText();
signals:
    void signalFilter(QVector<QVector<QString> >);
public slots:
    void slotFilter(QString colName="");
    void slotClear();
    void slotRefresh();
};

#endif // FILTERWIDGET_H
