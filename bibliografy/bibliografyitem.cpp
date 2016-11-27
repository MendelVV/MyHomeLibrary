#include "bibliografyitem.h"

BibliografyItem::BibliografyItem(QString tp, QString val):
    QGraphicsItem()
{
    y =((double)GetSystemMetrics(SM_CYSCREEN))/100;
    x =((double)GetSystemMetrics(SM_CXSCREEN))/100;
    type=tp;
    value=val;
}

void BibliografyItem::setValue(QString val){
    value=val;
}

QString BibliografyItem::getValue(){
    return value;
}

QString BibliografyItem::getType(){
    return type;
}

QRectF BibliografyItem::boundingRect() const
{
    QPointF ptPosition(0-nPenWidth,0-nPenWidth);
    QSizeF size;
    size.setWidth(6*x+nPenWidth);
    size.setHeight(3*y+nPenWidth);
    return QRectF(ptPosition,size);
}

void BibliografyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    painter->save();
    QColor color(125,125,255);
    QColor colorE(230,255,230,180);//элемент
    QColor colorS(255,230,230,180);//разделитель
    painter->setPen(QPen(color, nPenWidth));
    if (type=="Э"){
        painter->setBrush(QBrush(colorE));
    }else{
        painter->setBrush(QBrush(colorS));
    }
    painter->drawRect(0,0,4*x,3*y);

    painter->setPen(QPen(Qt::black, nPenWidth));
    QFont font("Times",QApplication::font().pointSize()-1);
    painter->setFont(font);
    QFontMetrics fontm (font);
    QString str = value;
    while (fontm.width(str)>4*x-4){
        str=str.left(str.length()-1);
    }
    painter->drawText(4,3*y-5,str);
    painter->restore();
}

void BibliografyItem::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if (event->button()==1){
        setZValue(1);
        setFlags(QGraphicsItem::ItemIsMovable);
    }
    QGraphicsItem::mousePressEvent(event);
}

void BibliografyItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsItem::mouseReleaseEvent(event);
    setFlags(QGraphicsItem::ItemIsSelectable);
}
