#include "dialogtypesbook.h"

DialogTypesBook::DialogTypesBook(SQLClass* dbC, QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Типы изданий");
    db = dbC;
    setModal(true);
    double x =((double)GetSystemMetrics(SM_CXSCREEN))/100;
    double y =((double)GetSystemMetrics(SM_CYSCREEN))/100;
    form = new FormPlusData;
    CellPlusClass* cell;
    cell = new CellPlusClass("lblTitle", "Label", "Список типов изданий", 0, 0, 19, 3);
    cell->setMergeColumn(2);
    cell->setFont(QFont("Times",9));
    cell->setColor(QColor(137,202,200,255));
    cell->setAlignment("Center");
    form->addCell(cell);

    cell = new CellPlusClass("fldTypeBook", "Completer", "", 1, 0, 19, 3);

    QStringList lst = db->selectQueryColumnAsList("SELECT type FROM tableBooksTypes ORDER BY type ASC;");
    cell->setList(lst);
    cell->setMergeColumn(2);
    form->addCell(cell);

    cell = new CellPlusClass("butAdd", "Button", "Добавить", 2, 0, 9, 3);
    connect(cell,SIGNAL(signalPress()),this,SLOT(slotAdd()));
    form->addCell(cell);

    cell = new CellPlusClass("butRemove", "Button", "Удалить", 2, 1, 9, 3);
    connect(cell,SIGNAL(signalPress()),this,SLOT(slotRemove()));
    form->addCell(cell);

    cell = new CellPlusClass("butOk", "Button", "Ok", 4, 0, 9, 3);
    connect(cell,SIGNAL(signalPress()),this,SLOT(slotAccept()));
    form->addCell(cell);

    cell = new CellPlusClass("butCancel", "Button", "Отмена", 4, 1, 9, 3);
    connect(cell,SIGNAL(signalPress()),this,SLOT(reject()));
    form->addCell(cell);

    listW = new QListWidget;
    listW->addItems(lst);
    listW->setFixedSize(19*x,18*y);

    LayoutToForm* ltf = new LayoutToForm;
    ltf->addFormData(form);
    ltf->addWidget(listW,3,0,1,2);
    ltf->setMargin(x/2);
    setLayout(ltf);

    QPalette pal;
    QColor color(255,255,185);//(234,252,250);
    pal.setColor(backgroundRole(),color);
    setPalette(pal);
}

DialogTypesBook::~DialogTypesBook(){
    delete form;
}

void DialogTypesBook::slotAdd(){
    QStringList lst = form->getCell("fldTypeBook")->getList();//список типов книг
    if (!lst.contains(form->getValue("fldTypeBook"))&&form->getValue("fldTypeBook")!=""){
        listW->addItem(form->getValue("fldTypeBook"));//добавили
        lst<<form->getValue("fldTypeBook");
        form->getCell("fldTypeBook")->setList(lst);
        form->getCell("fldTypeBook")->setValue("");
        form->getCell("fldTypeBook")->changeValueWidget();
    }else{
        QMessageBox* msb = new QMessageBox(this);
        msb->setWindowTitle("Ошибка!");
        msb->setText("Уже есть такой тип издания!");
        msb->show();
    }
}

void DialogTypesBook::slotRemove(){
    QStringList lst = form->getCell("fldTypeBook")->getList();//список типов книг
    QListWidgetItem* lItem = listW->currentItem();
    if (lItem!=0){
        lst.removeAll(lItem->text());
        listW->clear();
        listW->addItems(lst);
        form->getCell("fldTypeBook")->setList(lst);
    }else{
        QMessageBox* msb = new QMessageBox(this);
        msb->setWindowTitle("Ошибка!");
        msb->setText("Не выбран тип издания для удаления!");
        msb->show();
    }
}

void DialogTypesBook::slotAccept(){
    //перебираем список типов и список того что в виджете
    QVector<QString> lstOld = db->selectQueryColumn("SELECT type FROM tableBooksTypes ORDER BY type ASC;");
    QStringList lstNew = form->getCell("fldTypeBook")->getList();//список типов книг
    QVector<QString> lstNums = db->selectQueryColumn("SELECT code FROM tableBooksTypes ORDER BY code DESC;");
    int num = lstNums[0].toInt()+1;
    QVector<QString> vecAdd;//что добавить
    SQLCursor* cur = new SQLCursor;
    cur->putColumn("code",SQLCursor::INT);
    cur->putColumn("type",SQLCursor::VARCHAR);

    int n = lstNew.count();
    for (int i=0;i<n;i++){
        //сравниваем
        if (lstOld.contains(lstNew[i])){
            //если есть в старом значит не добавляем
            lstOld.removeAll(lstNew[i]);
        }else{
            //если в таром такого небыло то отмечаем что нужно будет добавить
            vecAdd.clear();
            num++;
            vecAdd<<QString::number(num);
            vecAdd<<lstNew[i];
            cur->putLine(vecAdd);
        }
    }
    //в итоге cur - содержит все новые
    //lstOld - содержит все что нужно удалить
    db->insertData("tableBooksTypes",cur);
    delete cur;
    //для того что удаляем отдельные операции проводим
    n = lstOld.count();
    QString whereStr="";
    for (int i=0;i<n;i++){
        //узнаем для каждого значение точно ли его нужно удалить
        //диалог про удаление и замену

        FormPlusData* formP = new FormPlusData;
        CellPlusClass* cell;
        cell = new CellPlusClass("lblTitle", "Label", "Выберите на что заменить \""+lstOld[i]+"\":", 0, 0, 16, 3);
        cell->setMergeColumn(2);
        cell->setFont(QFont("Times",9));
        cell->setColor(QColor(137,202,200,255));
        cell->setAlignment("Center");
        formP->addCell(cell);

        cell = new CellPlusClass("fldTypeBook", "Combobox", "", 1, 0, 16, 3);
        cell->setList(form->getCell("fldTypeBook")->getList());
        cell->setMergeColumn(2);
        formP->addCell(cell);

        cell = new CellPlusClass("butOk", "Button", "Ок", 2, 0, 8, 3);
        formP->addCell(cell);

        cell = new CellPlusClass("butCancel", "Button", "Отмена", 2, 1, 8, 3);
        formP->addCell(cell);

        cur = new SQLCursor;
        QVector<QString> line;
        QVector<QString> vecWhereStr;
        cur->putColumn("bookType",SQLCursor::VARCHAR);
        DialogInForm* dlg = new DialogInForm(formP,this);
        if (dlg->exec()==QDialog::Accepted){
            whereStr = "type='"+lstOld[i]+"'";
            db->deleteWhereData("tableBooksTypes",whereStr);
            //удалили тип книги

            if (dlg->form->getValue("fldTypeBook")!=""){
            //заменяем теперь если есть на что
                line.clear();
                line<<dlg->form->getValue("fldTypeBook");
                cur->putLine(line);
                vecWhereStr<<"bookType='"+lstOld[i]+"'";
            }


        }
        db->updateData("tableBooks",cur,vecWhereStr);
        delete cur;
        delete dlg;
    }
    accept();
}
