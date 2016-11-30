#include "bibliografytable.h"

BibliografyTable::BibliografyTable(QVector<QVector<QString> >  dt, QWidget *parent) :
    QTableWidget(parent)
{
    y =((double)GetSystemMetrics(SM_CYSCREEN))/100;
    x =((double)GetSystemMetrics(SM_CXSCREEN))/100;
    int n=5;
    for (int i=0;i<n;i++){
        insertColumn(i);
    }
    setColumnWidth(0,2*x);
    setColumnHidden(1,true);
    setColumnWidth(2,28*x);
    setColumnWidth(3,10*x);
    setColumnWidth(4,18*x);
    QStringList lst;
    lst<<""<<"code"
      <<tr("String")
     <<tr("Book type","main")//"Тип издания"
    <<tr("Note","main");
    setHorizontalHeaderLabels(lst);
    setFixedSize(60*x,30*y);
    setAlternatingRowColors(true);
    n = dt.count();
    for (int i=0;i<n;i++){
        addRow(dt[i]);//добавляем строку и данные в data
    }
    connect(this,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(slotSelectItem(QTableWidgetItem*)));
    contMenu = new QMenu;
    QAction* actRemove = new QAction(tr("Remove"),0);
    connect(actRemove,SIGNAL(triggered(bool)),this,SLOT(slotRemove()));

    contMenu->addAction(actRemove);
}

void BibliografyTable::addRow(QVector<QString> rw){
    if (rw.count()!=columnCount()){
        return;//не совпали размерности - остановили
    }
    int n = rowCount();
    insertRow(n);
    setRowHeight(n,y*5);
    int m = rw.count();
    QTableWidgetItem* tItem;
    for (int i=0;i<m;i++){
        if (i>0){
            if (i==2){
                tItem = new QTableWidgetItem(toNormalString(rw[i]));
            }else{
                tItem = new QTableWidgetItem(rw[i]);
            }

            setItem(n,i,tItem);
            Qt::ItemFlags flags = tItem->flags();
            flags |=Qt::ItemIsSelectable;
            flags &=~Qt::ItemIsEditable;
            tItem->setFlags(flags);
        }else{
            tItem = new QTableWidgetItem();
            tItem->setFlags(tItem->flags() & ~Qt::ItemIsEditable);
            if (rw[0]=="1"){
                tItem->setCheckState(Qt::Checked);
            }else{
                tItem->setCheckState(Qt::Unchecked);
            }
            setItem(n,i,tItem);
        }
    }
    data<<rw;
}

void BibliografyTable::editRow(QVector<QString> rw){
    int n = rowCount();
    for (int i=0;i<n;i++){
        if (item(i,1)->text()==rw[0]){
            for (int j=1;j<rw.count();j++){
                if (j==1){
                    item(i,j+1)->setText(toNormalString(rw[j]));
                }else{
                    item(i,j+1)->setText(rw[j]);
                }

            }
            break;
        }
    }
}

QString BibliografyTable::toNormalString(QString str){
    QString res="";
    QStringList list = str.split("%%");
    int n = list.count();//всего элементов
    QMap<QString, QString> map;//словарь что на что менять

    map["author"]=tr("Author","main");//"Автор";
    map["authors"]=tr("Authors","main");//"Авторы";
    map["publicationYear"]=tr("Publication year","main");//"Год издания";
    map["publicationCity"]=tr("City","main");//Город";
    map["bookName"]=tr("Title","main");//"Название";
    map["publicationName"]=tr("Publication House","main");//"Издательство";
    map["pages"]=tr("Pages","main");//"Страницы";
    map["bookType"]=tr("Book type","main");"Тип издания";

    for (int i=0;i<n;i++){
        if (map.contains(list[i])){
            res=res+map[list[i]];
        }else{
            res=res+list[i];
        }
    }
    return res;
}

void BibliografyTable::mousePressEvent(QMouseEvent *event){
    QTableWidgetItem* tItem = itemAt(event->pos());
    if (tItem!=0){
        selectRow(tItem->row());
    }
}

void BibliografyTable::mouseDoubleClickEvent(QMouseEvent *event){
    QTableWidgetItem* tItem = itemAt(event->pos());
    if (tItem!=0){
        QString code = item(tItem->row(),1)->text();
        emit signalOpen(code);
    }
}

void BibliografyTable::contextMenuEvent(QContextMenuEvent *event){
    QTableWidgetItem* tItem = itemAt(event->pos());
    if (tItem!=0){
        contMenu->exec(event->globalPos());
    }
}

void BibliografyTable::slotSelectItem(QTableWidgetItem *tItem){
    if (tItem->column()!=0) return;
    if (tItem->checkState()==Qt::Checked){
        QString type = item(tItem->row(),3)->text();
        //если выбрали то проверяем не выбран ли другой с таким же типом
        int n = rowCount();
        for (int i=0;i<n;i++){
            if(i!=tItem->row() && item(i,3)->text()==type){
                QTableWidgetItem* eItem = item(i,0);
                eItem->setCheckState(Qt::Unchecked);
            }
        }
    }
}

void BibliografyTable::slotRemove(){
    QTableWidgetItem* tItem = item(currentRow(),1);
    if (tItem==0) return;
    QString code = tItem->text();
    emit signalRemove(code);
    removeRow(currentRow());
}
