#include "filterwidget.h"

FilterWidget::FilterWidget(SQLClass* dbC, BooksTable* tab, QWidget *parent) :
    QMainWindow(parent)
{
    db = dbC;
    table = tab;
    form = new FormPlusData;
    form->readFormPlusData(":/resource/FormFilterWidget.cfpoq");
    slotRefresh();
    //слоты подключаем

    connect(form->getCell("butFilter"),SIGNAL(signalPress()),this,SLOT(slotFilter()));
    connect(form->getCell("butClear"),SIGNAL(signalPress()),this,SLOT(slotClear()));

    LayoutToForm* ltf = new LayoutToForm;
    ltf->addFormData(form);
    ScrollWidget* sc = new ScrollWidget(ltf);

    setCentralWidget(sc);
}

void FilterWidget::slotFilter(QString colName){
//строим сначала условия
    QString whereStr="";
    if (form->getValue("fldAuthor")!=""){
        if (whereStr!="") whereStr=whereStr+" AND ";
        whereStr=whereStr+"authors LIKE \"%"+form->getValue("fldAuthor")+"%\"";
    }
    if (form->getValue("fldCategory")!=""){
        if (whereStr!="") whereStr=whereStr+" AND ";
        QStringList lst = form->getValue("fldCategory").split("; ");

        for (int i=0;i<lst.count();i++){
            if (i==0){
                whereStr=whereStr+"(category LIKE \"%"+lst[i]+"%\"";
            }else{
                whereStr=whereStr+" OR category LIKE \"%"+lst[i]+"%\"";
            }
        }
        whereStr=whereStr+")";
    }

    if (form->getValue("fldSubcategory")!=""){
        if (whereStr!="") whereStr=whereStr+" AND ";
        QStringList lst = form->getValue("fldSubcategory").split("; ");

        for (int i=0;i<lst.count();i++){
            if (i==0){
                whereStr=whereStr+"(subcategory LIKE \"%"+lst[i]+"%\"";
            }else{
                whereStr=whereStr+" OR subcategory LIKE \"%"+lst[i]+"%\"";
            }
        }
        whereStr=whereStr+")";
    }

    if (form->getValue("fldTypeBook")!=""){
        if (whereStr!="") whereStr=whereStr+" AND ";
        QStringList lst = form->getValue("fldTypeBook").split("; ");

        for (int i=0;i<lst.count();i++){
            if (i==0){
                whereStr=whereStr+"(bookType LIKE \"%"+lst[i]+"%\"";
            }else{
                whereStr=whereStr+" OR bookType LIKE \"%"+lst[i]+"%\"";
            }
        }
        whereStr=whereStr+")";
    }
    QVector<QString> cols;
    cols<<"code"<<"category"<<"subcategory"<<"bookName"<<"authors";
    QVector<QString> sort;
    sort<<"category"<<"subcategory"<<"bookName";
    if (colName!=""){
        sort.removeAll(colName);
        sort.insert(0,colName);
    }
    QVector<QVector<QString> >data = db->select("tableBooks",cols,whereStr,sort);

    if (form->getValue("fldBookName")!=""){
        int n = data.count();
        for (int i=n-1;i>=0;i--){
            QString val = data[i][3].toLower();
            if (!val.contains(form->getValue("fldBookName").toLower())){
                data.remove(i);
            }
        }
    }
    if (form->getValue("fldSelected")!=""){
        QVector<QString> codes = table->getSelected();
        int n = data.count();
        for (int i=n-1;i>=0;i--){
            if (form->getValue("fldSelected")=="Да" && !codes.contains(data[i][0])){
                data.remove(i);
            }else if (form->getValue("fldSelected")=="Нет" && codes.contains(data[i][0])){
                data.remove(i);
            }
        }
    }
    emit signalFilter(data);
}

void FilterWidget::slotClear(){
    form->getCell("fldBookName")->setValue("");
    form->getCell("fldAuthor")->setValue("");
    form->getCell("fldCategory")->setValue("");
    form->getCell("fldSubcategory")->setValue("");
    form->getCell("fldTypeBook")->setValue("");
    form->getCell("fldSelected")->setValue("");

    form->getCell("fldBookName")->changeValueWidget();
    form->getCell("fldAuthor")->changeValueWidget();
    form->getCell("fldCategory")->changeValueWidget();
    form->getCell("fldSubcategory")->changeValueWidget();
    form->getCell("fldTypeBook")->changeValueWidget();
    form->getCell("fldSelected")->changeValueWidget();

    QString qr = "SELECT code, category, subcategory, bookName, authors FROM tableBooks ORDER BY category, subcategory, bookName ASC";
    QVector<QVector<QString> > data = db->getQueryData(qr);//взяли нужные данные, но здесь у нас  часть сразу готова
    emit signalFilter(data);
}

void FilterWidget::slotRefresh(){
    QStringList compList;
    QStringList tempList;
    compList = db->selectQueryColumnAsList("SELECT type FROM tableBooksTypes ORDER BY type ASC");
    form->getCell("fldTypeBook")->setList(compList);
    compList = db->selectQueryColumnAsList("SELECT DISTINCT category FROM tableBooks ORDER BY category ASC");
    form->getCell("fldCategory")->setList(compList);
    //с автором и с подкатегориями немножко иначе
    compList.clear();
    tempList = db->selectQueryColumnAsList("SELECT DISTINCT subcategory FROM tableBooks ORDER BY subcategory ASC");
    int n = tempList.count();
    for (int i=0;i<n;i++){
        if (tempList[i].contains("; ")){
        //если это неколько категорий
            QStringList vals = tempList[i].split("; ");
            int m = vals.count();
            for (int j=0;j<m;j++){
                if (!compList.contains(vals[j])){
                    compList<<vals[j];
                }
            }
        }else{
            if (!compList.contains(tempList[i])){
                compList<<tempList[i];
            }
        }
    }
    form->getCell("fldSubcategory")->setList(compList);
    compList.clear();
    tempList = db->selectQueryColumnAsList("SELECT DISTINCT authors FROM tableBooks ORDER BY authors ASC");
    n = tempList.count();
    for (int i=0;i<n;i++){
        if (tempList[i].contains("; ")){
        //если это неколько категорий
            QStringList vals = tempList[i].split("; ");
            int m = vals.count();
            for (int j=0;j<m;j++){
                if (!compList.contains(vals[j])){
                    compList<<vals[j];
                }
            }
        }else{
            if (!compList.contains(tempList[i])){
                compList<<tempList[i];
            }
        }
    }
    form->getCell("fldAuthor")->setList(compList);
    form->slotRefreshWidgetsValues();
}
