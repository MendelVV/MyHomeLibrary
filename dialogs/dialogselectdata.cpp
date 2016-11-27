#include "dialogselectdata.h"

DialogSelectData::DialogSelectData(QString columnName, SQLClass* dbC, QVector<QString> vals, QWidget *parent) :
    QDialog(parent)
{
    //vals - список значений которые есть
    setModal(true);
    //считываем сначала список всего что есть
    db = dbC;
    QString qr = "SELECT DISTINCT "+columnName+" FROM tableBooks;";
    vecVal = db->selectQueryColumn(qr);
    //получили все возможные значения
    //сначала вставляем поле и кнопку для добавления нового
    x =((double)GetSystemMetrics(SM_CXSCREEN))/100;
    y =((double)GetSystemMetrics(SM_CYSCREEN))/100;

    text = new QLineEdit;
    text->setFixedWidth(15*x);

    butAdd = new QPushButton("+");
    butAdd->setFixedWidth(4*x);
    connect(butAdd,SIGNAL(clicked(bool)),this,SLOT(slotAddValue()));

    lwgt = new QListWidget;
    setFixedSize(20*x,25*y);
    int n = vecVal.count();
    for (int i=0;i<n;i++){
        QListWidgetItem* item = new QListWidgetItem(vecVal[i]);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        if (vals.contains(vecVal[i])){
            item->setCheckState(Qt::Checked);
        }else{
            item->setCheckState(Qt::Unchecked);
        }
        lwgt->addItem(item);
    }

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(text,0,0);
    layout->addWidget(butAdd,0,1);
    layout->addWidget(lwgt,1,0,1,2);
    QHBoxLayout* ltb = new QHBoxLayout;
    QPushButton* butOk = new QPushButton("Оk");
    connect(butOk,SIGNAL(clicked(bool)),this,SLOT(accept()));
    QPushButton* butCancel = new QPushButton("Отмена");
    connect(butCancel,SIGNAL(clicked(bool)),this,SLOT(reject()));
    ltb->addWidget(butOk);
    ltb->addWidget(butCancel);
    layout->addLayout(ltb,2,0,1,2);
    setLayout(layout);
}

void DialogSelectData::slotAddValue(){
    QString val = text->text();
    if (val==""){
        return;
    }
    if (vecVal.contains(val)){
        //ищем соответсвующий пункт списка
        QListWidgetItem* item = lwgt->item(vecVal.indexOf(val));
        item->setCheckState(Qt::Checked);
    }else{
        //добавляем новый пункт списка
        QListWidgetItem* item = new QListWidgetItem(val);
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Checked);
        vecVal<<val;
    }
}
