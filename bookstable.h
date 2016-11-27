#ifndef BOOKSTABLE_H
#define BOOKSTABLE_H

#include <QtWidgets>

class BooksTable : public QTableWidget
{
    Q_OBJECT
public:
    explicit BooksTable(QVector<QVector<QString> > dt, QWidget *parent = 0);
    QVector<QVector<QString> > data;
    QVector<QString> getSelected();
    void deselectAll();
protected:
    QVector<QString> codes;
//    QVector<QTableWidgetItem*> headers;
    double x;
    double y;
    void refresh();
//    QColor colorRow;
    QMenu* contMenu;

    void contextMenuEvent(QContextMenuEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

signals:
    void signalSelected(int);
    void signalOpenBook(QString);
    void signalOpenBookFile(QString);
    void signalSort(QString colName);
public slots:
    void slotRefresh(QVector<QVector<QString> > dt);
    void slotSelectItem(QTableWidgetItem*);
    void slotSort(int);
    void slotOpenBook();
    void slotOpenBookFile();
    void slotSelectAll();
};

#endif // BOOKSTABLE_H
