#include "bibliografylist.h"

BibliografyList::BibliografyList(SQLClass* dbC, QWidget *parent) :
    QMainWindow(parent)
{
    y =((double)GetSystemMetrics(SM_CYSCREEN))/100;
    x =((double)GetSystemMetrics(SM_CXSCREEN))/100;
    db = dbC;

    QVector<QString> cols;
    cols<<"selected"<<"code"<<"value"<<"type"<<"note";
    QVector<QString> sort;
    QVector<QVector<QString> > vec = db->select("tableBibliografy",cols,"",sort);
    table = new BibliografyTable(vec);
    connect(table,SIGNAL(signalOpen(QString)),this,SLOT(slotOpen(QString)));
    connect(table,SIGNAL(signalRemove(QString)),this,SLOT(slotRemove(QString)));

    setFixedWidth(60*x);
//    setFixedSize(50*x,34*y);
//все действия на панели меню
    setCentralWidget(table);
    setActMenu();
    menuBar()->addAction(actSave);
    menuBar()->addAction(actSaveAndClose);
    menuBar()->addAction(actAdd);
    menuBar()->addAction(actClose);
}

void BibliografyList::setActMenu(){
    actAdd = new QAction("Добавить",0);
    connect(actAdd,SIGNAL(triggered(bool)),this,SLOT(slotAdd()));

    actSave = new QAction("Сохранить",0);
    connect(actSave,SIGNAL(triggered(bool)),this,SLOT(slotSave()));

    actSaveAndClose = new QAction("Сохранить и закрыть",0);
    connect(actSaveAndClose,SIGNAL(triggered(bool)),this,SLOT(slotSaveAndClose()));

    actClose = new QAction("Закрыть",0);
    connect(actClose,SIGNAL(triggered(bool)),this,SLOT(close()));
}

void BibliografyList::slotAdd(){
    QString qr = "SELECT type FROM tableBooksTypes ORDER BY type ASC;";
    QStringList lst = db->selectQueryColumnAsList(qr);
    lst.insert(0,"Общий");
    BibliografyWindow* bw = new BibliografyWindow(lst, 0, this);
    bw->move(20*x,20*y);
    connect(bw,SIGNAL(signalSave(BibliografyClass*)),this,SLOT(slotAddInDb(BibliografyClass*)));
    bw->show();
}

void BibliografyList::slotAddInDb(BibliografyClass *bibC){
    int count = db->selectCount("tableBibliografy");
    int nm;
    if (count>0){
        QVector<QString> vec = db->selectQueryColumn("SELECT code FROM tableBibliografy ORDER BY code DESC;");
        nm = vec[0].toInt()+1;
    }else{
        nm=1;
    }
    SQLCursor* cur = new SQLCursor;
    cur->putColumn("selected",SQLCursor::INT);
    cur->putColumn("code",SQLCursor::INT);
    cur->putColumn("value",SQLCursor::VARCHAR);
    cur->putColumn("type",SQLCursor::VARCHAR);
    cur->putColumn("note",SQLCursor::VARCHAR);
    QVector<QString> line;
    line<<"0"<<QString::number(nm)<<bibC->getValue()<<bibC->getType()<<bibC->getNote();
    cur->putLine(line);
    db->insertData("tableBibliografy",cur);
    delete cur;
    delete bibC;
    //обновить вид
    table->addRow(line);
    //ну или просто добавить новую строку
}

void BibliografyList::slotEditInDb(BibliografyClass *bibC){
    SQLCursor* cur = new SQLCursor;
    cur->putColumn("code",SQLCursor::INT);
    cur->putColumn("value",SQLCursor::VARCHAR);
    cur->putColumn("type",SQLCursor::VARCHAR);
    cur->putColumn("note",SQLCursor::VARCHAR);
    QVector<QString> line;
    line<<bibC->getCode()<<bibC->getValue()<<bibC->getType()<<bibC->getNote();
    cur->putLine(line);
    QVector<QString> vecWhere;
    vecWhere<<"code="+bibC->getCode();
    db->updateData("tableBibliografy",cur,vecWhere);
    delete cur;
    delete bibC;
    table->editRow(line);
    //обновить вид

    //ну или просто добавить новую строку
}

void BibliografyList::slotOpen(QString code){
    QVector<QString> cols;
    cols<<"selected"<<"code"<<"value"<<"type"<<"note";
    QVector<QString> sort;
    QString whereStr="code="+code;
    QVector<QVector<QString> > vec = db->select("tableBibliografy",cols,whereStr,sort);
    BibliografyClass* bibC = new BibliografyClass(vec[0][1],vec[0][3],vec[0][2],vec[0][4]);

    QString qr = "SELECT type FROM tableBooksTypes ORDER BY type ASC;";
    QStringList lst = db->selectQueryColumnAsList(qr);
    lst.insert(0,"Общий");
    BibliografyWindow* bw = new BibliografyWindow(lst, bibC, this);
    bw->move(20*x,20*y);
    connect(bw,SIGNAL(signalSave(BibliografyClass*)),this,SLOT(slotEditInDb(BibliografyClass*)));
    bw->show();
}

void BibliografyList::slotRemove(QString code){
    db->deleteWhereData("tableBibliografy","code="+code);
}

void BibliografyList::slotSave(){
    QMap<QString, QString> map = db->selectAsMap("tableBibliografy","code","selected","");
    int n = table->rowCount();
    QVector<QString> vecWhere;
    QVector<QString> line;
    for (int i=0;i<n;i++){
        line.clear();
        QTableWidgetItem* tItem = table->item(i,0);
        if (tItem->checkState()==Qt::Checked){
            line<<"1";
        }else{
            line<<"0";
        }
        if (map[table->item(i,1)->text()]==line[0])break;

        SQLCursor cur;
        cur.putColumn("selected",SQLCursor::INT);
        vecWhere.clear();
        cur.putLine(line);
        vecWhere<<"code="+table->item(i,1)->text();
        db->updateData("tableBibliografy",&cur,vecWhere);
    }
}

void BibliografyList::slotSaveAndClose(){
    slotSave();
    close();
}
