#ifndef BIBLIOGRAFYTABLE_H
#define BIBLIOGRAFYTABLE_H

#include <QtWidgets>

class BibliografyTable : public QTableWidget
{
    Q_OBJECT
public:
    explicit BibliografyTable(QVector<QVector<QString> >  dt, QWidget *parent = 0);
    void addRow(QVector<QString> rw);
    void editRow(QVector<QString> rw);
protected:
    QVector<QVector<QString> > data;
    double x;
    double y;
    QString toNormalString(QString);
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *);

    QMenu* contMenu;

signals:
    void signalOpen(QString);
    void signalRemove(QString);
public slots:
    void slotSelectItem(QTableWidgetItem *tItem);
    void slotRemove();
};

#endif // BIBLIOGRAFYTABLE_H
