#ifndef BIBLIOGRAPHIWINDOW_H
#define BIBLIOGRAPHIWINDOW_H

#include "layouttoform.h"
#include "bibliografyview.h"
#include "bibliografyitem.h"
#include "bibliografyclass.h"

class BibliografyWindow : public QDialog
        //QMainWindow
{
    Q_OBJECT
public:
    explicit BibliografyWindow(QStringList typesBk, BibliografyClass* bibC, QWidget *parent = 0);
protected:
    BibliografyClass* bibCls;
    QStringList typesBook;
    QGraphicsScene* scene;
    FormPlusData* form;
    qreal itemW;
    qreal lineY;
    qreal widthS;
    double x;
    double y;
    void addItem(QString tp);
    QVector<BibliografyItem*> vecItems;//вектор всех элементов
    void setLine(QString str);
signals:
    void signalSave(BibliografyClass*);
public slots:
    void slotItemPosition(BibliografyItem*);
    void slotRemoveItem(BibliografyItem*);
    void slotAdd();
};

#endif // BIBLIOGRAPHIWINDOW_H
