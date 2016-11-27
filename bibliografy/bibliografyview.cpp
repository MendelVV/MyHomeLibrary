#include "bibliografyview.h"

BibliografyView::BibliografyView(QGraphicsScene* parent) :
    QGraphicsView(parent)
{
    setAcceptDrops(true);
    currentItem=0;
    //определяем контекстное меню
    contMenu = new QMenu(this);
    //значение
    QAction* actValue = new QAction("Значение",0);
    connect(actValue,SIGNAL(triggered(bool)),this,SLOT(slotValue()));
    //удалить
    QAction* actRemove = new QAction("Удалить",0);
    connect(actRemove,SIGNAL(triggered(bool)),this,SLOT(slotRemove()));

    contMenu->addAction(actValue);
    contMenu->addAction(actRemove);
}

void BibliografyView::contextMenuEvent(QContextMenuEvent *ce){
    QGraphicsItem* bItem = itemAt(ce->pos());
    if (bItem!=0){
        if (bItem->type()==65536){
            currentItem = (BibliografyItem*) bItem;
            contMenu->exec(ce->globalPos());
        }
    }
}

void BibliografyView::mouseReleaseEvent(QMouseEvent *event){
    if (event->button()==1){
        QGraphicsItem* item = itemAt(event->pos());
        if (item!=0){
            if (item->type()==65536){
                currentItem = (BibliografyItem*) item;
                //отпустили мышь, проверили что под нами находится поле, выравниваем его по строке
                //точнее отправляем сигнал что нужно выровнять по строке
                emit signalPositionItem(currentItem);
                currentItem->setZValue(0);
            }
        }

    }
    QGraphicsView::mouseReleaseEvent(event);
}

void BibliografyView::slotRemove(){
    if (currentItem!=0){
        emit signalRemove(currentItem);
        currentItem=0;
    }
}

void BibliografyView::slotValue(){
    //собираем небольшое диалоговое окно и открываем его в зависимости от типа

    FormPlusData* form = new FormPlusData;
    CellPlusClass* cell;
    cell = new CellPlusClass("lblTitle", "Label", "Значение", 0, 0, 10, 3);
    cell->setMergeColumn(2);
    cell->setAlignment("Center");
    form->addCell(cell);
    if (currentItem->getType()=="Э"){
        cell = new CellPlusClass("fldValue", "Combobox", currentItem->getValue(), 1, 0, 10, 3);
        cell->setMergeColumn(2);
        cell->setList(QStringList()<<"Автор"<<"Авторы"<<"Год издания"<<"Город"<<"Название"<<"Издательство"<<"Страницы"<<"Тип издания");
        form->addCell(cell);
    }else{
        cell = new CellPlusClass("fldValue", "Text", currentItem->getValue(), 1, 0, 10, 3);
        cell->setMergeColumn(2);
        form->addCell(cell);
    }
    cell = new CellPlusClass("butOk", "Button", "Ok", 2, 0, 5, 3);
    form->addCell(cell);

    cell = new CellPlusClass("butCancel", "Button", "Отмена", 2, 1, 5, 3);
    form->addCell(cell);

    DialogInForm* dlg = new DialogInForm(form,this);
    dlg->setWindowTitle(" ");
    dlg->move(cursor().pos());
    if (dlg->exec()==QDialog::Accepted){
        currentItem->setValue(dlg->form->getValue("fldValue"));
    }
    delete dlg;
}
