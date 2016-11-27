#ifndef BIBLIOGRAFYVIEW_H
#define BIBLIOGRAFYVIEW_H

#include <QtWidgets>
#include "bibliografyitem.h"
#include "dialogs/dialoginform.h"

class BibliografyView : public QGraphicsView{
    Q_OBJECT
public:
    explicit BibliografyView(QGraphicsScene* parent = 0);
protected:
    BibliografyItem* currentItem;
    QMenu* contMenu;
    void contextMenuEvent(QContextMenuEvent *ce);
    void mouseReleaseEvent(QMouseEvent *event);
signals:
    void signalPositionItem(BibliografyItem*);
    void signalRemove(BibliografyItem*);
public slots:
    void slotRemove();
    void slotValue();
};

#endif // BIBLIOGRAFYVIEW_H
