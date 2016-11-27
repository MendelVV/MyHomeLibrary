#ifndef BIBLIOGRAFYITEM_H
#define BIBLIOGRAFYITEM_H

#include <QtWidgets>

class BibliografyItem : public QGraphicsItem
{
public:
    enum {nPenWidth=2};
    BibliografyItem(QString tp, QString val="");
    void setValue(QString);
    QString getValue();
    QString getType();
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
protected:
    double x;
    double y;
    QString value;//текст элемента
    QString type;//либо элемент, либо разделитель
};

#endif // BIBLIOGRAFYITEM_H
