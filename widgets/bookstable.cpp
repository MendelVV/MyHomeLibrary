#include "bookstable.h"

BooksTable::BooksTable(QVector<QVector<QString> > dt, QWidget *parent) :
    QTableWidget(parent)
{
    data = dt;//это само содержание таблицы
    //создаем саму таблицу
    x =((double)GetSystemMetrics(SM_CXSCREEN))/100;
    y =((double)GetSystemMetrics(SM_CYSCREEN))/100;

    int n = 6;//количество столбцов
    QStringList lst;
    lst<<""<<"code"
      <<tr("Category")//"Категория"
     <<tr("Subcategory")//"Подкатегория"
    <<tr("Title")//"Название"
    <<tr("Authors");//"Авторы";
    for (int i=0;i<n;i++){
        insertColumn(i);
    }
    setHorizontalHeaderLabels(lst);
    QHeaderView* hv = new QHeaderView(Qt::Horizontal);
    hv->setSectionsClickable(true);
    setHorizontalHeader(hv);
    connect(hv,SIGNAL(sectionClicked(int)),this,SLOT(slotSort(int)));
    setColumnWidth(0,2*x);
    setColumnHidden(1,true);//скрыли первую (типо вторую в первой галочки) колонку в которой код книги
    setColumnWidth(2,14*x);
    setColumnWidth(3,15*x);
    setColumnWidth(4,25*x);
    setColumnWidth(5,22*x);

    refresh();
    //colorRow=QColor(215,216,245);
    setAlternatingRowColors(true);
    contMenu = new QMenu;
    QAction* actOpenBook = new QAction(tr("Open card"),0);//"Открыть карточку"
    connect(actOpenBook,SIGNAL(triggered(bool)),this,SLOT(slotOpenBook()));
    contMenu->addAction(actOpenBook);

    QAction* actOpenBookFile = new QAction(tr("Open file"),0);//"Открыть файл"
    connect(actOpenBookFile,SIGNAL(triggered(bool)),this,SLOT(slotOpenBookFile()));
    contMenu->addAction(actOpenBookFile);
}

QVector<QString> BooksTable::getSelected(){
    return codes;
}

void BooksTable::deselectAll(){
    codes.clear();
    emit signalSelected(0);
}

void BooksTable::refresh(){
    disconnect(this,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(slotSelectItem(QTableWidgetItem*)));
    int n = rowCount();
    for (int i=0;i<n;i++){
        removeRow(0);
    }

    n = data.count();//количество строк
    for (int i=0;i<n;i++){
        insertRow(i);
        int m = columnCount();//количество столбцов
        QTableWidgetItem* item;
        for (int j=0;j<m;j++){
            if (j>0){
                item = new QTableWidgetItem(data[i][j-1]);
                setItem(i,j,item);
                Qt::ItemFlags flags = item->flags();
                flags |=Qt::ItemIsSelectable;
                flags &=~Qt::ItemIsEditable;
                item->setFlags(flags);
            }else{
                item = new QTableWidgetItem();
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
                if (codes.contains(data[i][0])){
                    item->setCheckState(Qt::Checked);
                }else{
                    item->setCheckState(Qt::Unchecked);
                }
                setItem(i,j,item);
            }
        }
    }
    connect(this,SIGNAL(itemChanged(QTableWidgetItem*)),this,SLOT(slotSelectItem(QTableWidgetItem*)));
}

void BooksTable::contextMenuEvent(QContextMenuEvent *event){
    QTableWidgetItem* tItem = itemAt(event->pos());
    if (tItem!=0){
        contMenu->exec(event->globalPos());
    }
}

void BooksTable::mousePressEvent(QMouseEvent *event){
    QTableWidgetItem* tbItem = itemAt(event->pos());
    if (tbItem!=0){
        selectRow(tbItem->row());
    }
}

void BooksTable::mouseDoubleClickEvent(QMouseEvent *event){
    if (event->buttons()==1){
        //берем код
        QTableWidgetItem* tbItem = item(currentRow(),1);
        if (tbItem!=0){
            emit signalOpenBookFile(tbItem->text());
        }
    }
}

void BooksTable::keyPressEvent(QKeyEvent *e){
    if (e->modifiers() & Qt::ControlModifier){
        switch (e->key()){
        case Qt::Key_A:
            //выбираем все
            slotSelectAll();
            break;
        default:
            QTableWidget::keyPressEvent(e);
        }
    }else{
        switch (e->key()){
        case Qt::Key_Up:
            if (currentRow()>0){
                selectRow(currentRow()-1);
            }
            break;
        case Qt::Key_Down:
            if (currentRow()<rowCount()){
                selectRow(currentRow()+1);
            }
            break;
        default:
            QTableWidget::keyPressEvent(e);
        }
    }
}

void BooksTable::slotRefresh(QVector<QVector<QString> > dt){
    data = dt;
    refresh();
}

void BooksTable::slotSelectItem(QTableWidgetItem *tItem){
    if (tItem->column()!=0) return;
    QTableWidgetItem* codeItem = item(tItem->row(),1);
    if (tItem->checkState()==Qt::Checked){
        codes<<codeItem->text();
    }else{
        codes.removeAll(codeItem->text());
    }
    emit signalSelected(codes.count());
}

void BooksTable::slotSort(int n){
    QString colName="";
    switch (n) {
    case 2:
        colName="category";
        break;
    case 3:
        colName="subcategory";
        break;
    case 4:
        colName="bookName";
        break;
    case 5:
        colName="authors";
        break;
    default:
        break;
    }
    if (colName!=""){
        emit signalSort(colName);
    }
}

void BooksTable::slotOpenBook(){
    QTableWidgetItem* tbItem = item(currentRow(),1);
    if (tbItem!=0){
        emit signalOpenBook(tbItem->text());
    }
}

void BooksTable::slotOpenBookFile(){
    QTableWidgetItem* tbItem = item(currentRow(),1);
    if (tbItem!=0){
        emit signalOpenBookFile(tbItem->text());
    }
}

void BooksTable::slotSelectAll(){
    //либо все выбирает либо снимает выбор со всего
    //ищем сначала первое вхождение не отмеченной книги
    codes.clear();
    bool b = true;
    for (int i=0;i<rowCount();i++){
        QTableWidgetItem* tItem = item(i,0);
        if (tItem->checkState()==Qt::Unchecked){
            //нашли не отмеченный
            b = false;
        }else{
            tItem->setCheckState(Qt::Unchecked);
        }
        tItem->setCheckState(Qt::Checked);//добавили к отмеченным
    }
    if (b){
        for (int i=0;i<rowCount();i++){
            QTableWidgetItem* tItem = item(i,0);
            tItem->setCheckState(Qt::Unchecked);
        }
    }
}
