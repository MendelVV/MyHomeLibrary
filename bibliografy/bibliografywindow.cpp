#include "bibliografywindow.h"

BibliografyWindow::BibliografyWindow(QStringList typesBk, BibliografyClass* bibC, QWidget *parent) :
    QDialog(parent)
    //QMainWindow(parent)
{
    setModal(true);
    setWindowTitle("Настройка оформления списка литературы");
    y =((double)GetSystemMetrics(SM_CYSCREEN))/100;
    x =((double)GetSystemMetrics(SM_CXSCREEN))/100;
    typesBook=typesBk;
    bibCls = bibC;
    form = new FormPlusData;
    scene = new QGraphicsScene(QRect(0,0,60*x,30*y));
    itemW=4*x;
    lineY=18*y;
    widthS=60;

    BibliografyView* view = new BibliografyView(scene);
    connect(view,SIGNAL(signalPositionItem(BibliografyItem*)),this,SLOT(slotItemPosition(BibliografyItem*)));
    connect(view,SIGNAL(signalRemove(BibliografyItem*)),this,SLOT(slotRemoveItem(BibliografyItem*)));
    QGraphicsLineItem* lnItem = scene->addLine(QLine(0,0,widthS*x,0),QPen(Qt::black,2));
    lnItem->moveBy(0,lineY-4*y);
    lnItem = scene->addLine(QLine(0,0,widthS*x,0),QPen(Qt::black,2));
    lnItem->moveBy(0,lineY+2);
    if (bibCls!=0){
        setLine(bibCls->getValue());
    }
    addItem("Э");
    addItem("Р");
//оформление
    QString str="<p align='justify'>Для создания строки библиографического списка перетаскивайте в строку нужные элементы. "
                "<font color='blue'>Синий прямоугольник</font> соответствует элементу относящемуся к книге (Автор, Название книги, Издательство и т.д.), "
                "<font color='red'>красный прямоугольник</font> соответствует некоторому разделителю (';', '- ', 'набор символов')."
                " Задать и изменить значение в элементе можно при помощи пункта 'Значение' контекстного меню. "
                "Так же в полях над строкой нужно указать тип издания для которого применяется такое оформление литературы"
                " и небольшое примечание, если оно нужно.<p>";
    CellPlusClass* cell;
    cell = new CellPlusClass("lblTitle","MultyLabel","",0,0,widthS,10);
    form->addCell(cell);
    MultyLabelCell* lbl = new MultyLabelCell(cell);
    lbl->setHtml(str);
    QGraphicsProxyWidget* gpw = scene->addWidget(lbl);
    gpw->moveBy(0,0);
    qreal dx=0;
    str = "Тип издания:";
    QGraphicsTextItem* gti = scene->addText(str);
    gti->moveBy(0,lineY-8*y);
    QFontMetrics mfont(gti->font());
    dx=mfont.width(str)+5;
    cell = new CellPlusClass("fldType","Combobox","",0,0,13);
    cell->setList(typesBook);
    if (bibCls!=0){
        cell->setValue(bibCls->getType());
    }
    form->addCell(cell);
    //нужно список добавить
    ComboBoxCell* cmb = new ComboBoxCell(cell);
    gpw = scene->addWidget(cmb);
    gpw->moveBy(dx,lineY-8*y);
    gpw->setZValue(2);

    str = "Примечание:";
    dx=dx+13*x+5;
    gti = scene->addText(str);
    gti->moveBy(dx,lineY-8*y);
    dx=dx+mfont.width(str)+5;
    cell = new CellPlusClass("fldNote", "Text", "", 0, 1, 35, 3);
    if (bibCls!=0){
        cell->setValue(bibCls->getNote());
    }
    form->addCell(cell);
    LineEditCell* text = new LineEditCell(cell);
    gpw = scene->addWidget(text);
    gpw->moveBy(dx,lineY-8*y);

    cell = new CellPlusClass("butOk","Button","Сохранить",0,0,6);
    form->addCell(cell);
    connect(cell,SIGNAL(signalPress()),this,SLOT(slotAdd()));
    ButtonCell* butOk = new ButtonCell(cell);
    gpw = scene->addWidget(butOk);
    gpw->moveBy(0,lineY+5*y);

    cell = new CellPlusClass("butCancel","Button","Отменить",0,0,6);
    form->addCell(cell);
    connect(cell,SIGNAL(signalPress()),this,SLOT(close()));
    ButtonCell* butCancel = new ButtonCell(cell);
    gpw = scene->addWidget(butCancel);
    gpw->moveBy(6*x+10,lineY+5*y);
//==========================
    view->setFixedSize(61*x,31*y);
    setFixedSize(61*x,31*y);
    QHBoxLayout* hlayout = new QHBoxLayout;
    hlayout->addWidget(view);
    hlayout->setMargin(0);
    setLayout(hlayout);

    //setCentralWidget(view);

}

void BibliografyWindow::addItem(QString tp){
    BibliografyItem* bItem = new BibliografyItem(tp);
    bItem->setFlags(QGraphicsItem::ItemIsMovable);
    scene->addItem(bItem);
    bItem->setZValue(1);
    if (tp=="Э"){
        bItem->moveBy(0,lineY+8);
    }else{
        bItem->moveBy(itemW+0.5*x,lineY+8);
    }
}

void BibliografyWindow::setLine(QString str){
    QStringList list = str.split("%%");
    int n = list.count();//всего элементов
    QMap<QString, QString> map;//словарь что на что менять
    map["author"]="Автор";
    map["authors"]="Авторы";
    map["publicationYear"]="Год издания";
    map["publicationCity"]="Город";
    map["bookName"]="Название";
    map["publicationName"]="Издательство";
    map["pages"]="Страницы";
    map["bookType"]="Тип издания";

    BibliografyItem* bItem;
    int pos = 0;
    for (int i=0;i<n;i++){
        if (map.contains(list[i])){
            bItem = new BibliografyItem("Э");
            bItem->setValue(map[list[i]]);
        }else{
            if (list[i]=="") break;
            bItem = new BibliografyItem("Р");
            bItem->setValue(list[i]);
        }
        bItem->setFlags(QGraphicsItem::ItemIsMovable);
        scene->addItem(bItem);
        bItem->setZValue(1);
        vecItems<<bItem;
        bItem->setPos(pos*(itemW+2),lineY-3*y);
        pos++;
    }
}

void BibliografyWindow::slotItemPosition(BibliografyItem *bItem){
//    qDebug()<<bItem->pos();//это верхний левый угол
    //проверяем что попали по высоте в нашу полосу. тогда ставим поле туда куда нужно
    qreal itemY = bItem->pos().y();
    qreal itemX = bItem->pos().x();
    if (itemY<lineY && itemY>lineY-7*y){
        //попали в полосу
        //теперь выравниваем по х и по y
        //ищем положение в строке считаем примерную позицию по x которая должа быть
        int posX =(int) (itemX+x/2)/(itemW+2);//целая часть от этого и есть
//        qDebug()<<posX;
        if (vecItems.contains(bItem)){
        //если мы перемещаем внутри строки
            int posCur = vecItems.indexOf(bItem);//текущее положение
            if (posCur!=posX){
                //удаляем и смещаем влево
                int n = vecItems.count()-1;
                vecItems.removeAll(bItem);
                for (int i=posCur;i<n;i++){
                    vecItems[i]->moveBy(-itemW-2,0);
                }
                for (int i=posX;i<vecItems.count();i++){
                    vecItems[i]->moveBy(itemW+2,0);
                }
                if (posX<vecItems.count()){
                    bItem->setPos(posX*(itemW+2),lineY-3*y);
                    vecItems.insert(posX,bItem);
                }else{
                    bItem->setPos(vecItems.count()*(itemW+2),lineY-3*y);
                    vecItems<<bItem;
                }
            }else{
                bItem->setPos(posX*(itemW+2),lineY-3*y);
            }
        }else{
            //если это новый элемент не из строки
            if (vecItems.count()<=posX){
                //когда вставляем явно в конец
                bItem->setPos(vecItems.count()*(itemW+2),lineY-3*y);
                vecItems<<bItem;
            }else{
                //вставляем в середину
                for (int i=posX;i<vecItems.count();i++){
                    vecItems[i]->moveBy(itemW+2,0);
                }
                bItem->setPos(posX*(itemW+2),lineY-3*y);
                vecItems.insert(posX,bItem);
            }
            //создаем новые
            addItem(bItem->getType());
        }

    }else{
        if (vecItems.contains(bItem)){
            //возвращаем на его место
            int posX = vecItems.indexOf(bItem);
            bItem->setPos(posX*(itemW+2),lineY-3*y);
        }else{
            //возвращаем в начало
            if (bItem->getType()=="Э"){
                bItem->setPos(0,lineY+8);
            }else{
                bItem->setPos(itemW+0.5*x,lineY+8);
            }
        }
    }
}

void BibliografyWindow::slotRemoveItem(BibliografyItem *bItem){
    int posX = vecItems.indexOf(bItem);
    if (posX<0) return;
    vecItems.removeAll(bItem);
    scene->removeItem(bItem);
    for (int i=posX;i<vecItems.count();i++){
        vecItems[i]->moveBy(-itemW-2,0);
    }
}

void BibliografyWindow::slotAdd(){
    //все дела
    if (form->getValue("fldType")==""){
        QMessageBox* msb = new QMessageBox(this);
        msb->setWindowTitle("Ошибка!");
        msb->setText("Не указан тип книг!");
        msb->show();
        return;
    }
    QString res="";
    int n = vecItems.count();
    for (int i=0;i<n;i++){
        if (vecItems[i]->getType()=="Э"){
            //если элемент книги. разделитель в строке %%
//<<"Автор"<<"Авторы"<<"Год издания"<<"Город"<<"Название"<<"Издательство"<<"Страницы"<<"Тип издания"
            if (vecItems[i]->getValue()=="Автор"){
                res=res+"author";
            }else if(vecItems[i]->getValue()=="Авторы"){
                res=res+"authors";
            }else if(vecItems[i]->getValue()=="Год издания"){
                res=res+"publicationYear";
            }else if(vecItems[i]->getValue()=="Город"){
                res=res+"publicationCity";
            }else if(vecItems[i]->getValue()=="Название"){
                res=res+"bookName";
            }else if(vecItems[i]->getValue()=="Издательство"){
                res=res+"publicationName";
            }else if(vecItems[i]->getValue()=="Страницы"){
                res=res+"pages";
            }else if(vecItems[i]->getValue()=="Тип издания"){
                res=res+"bookType";
            }
            res=res+"%%";
        }else{
            //если разделитель
            res=res+vecItems[i]->getValue()+"%%";
        }
    }
    res = res.left(res.length()-2);
    BibliografyClass* bibC;
    if (bibCls==0){
        bibC = new BibliografyClass("",form->getValue("fldType"), res,form->getValue("fldNote"));
    }else{
        bibC = bibCls;
        bibC->setValue(res);
        bibC->setType(form->getValue("fldType"));
        bibC->setNote(form->getValue("fldNote"));
    }
    emit signalSave(bibC);
    close();
    //"author%%bookName%%/ %%authors%%.- %%publicationCity%%: %%publicationName%%, %%publicationYear%%.- %%pages%% с.%%"
    //закрыть
}
