#include "searchwidget.h"

SearchWidget::SearchWidget(SQLClass* dbC, QWidget *parent) :
    QDialog(parent)
{
    setModal(true);
    db = dbC;
    form = new FormPlusData;
    form->readFormPlusData(":/resource/FormSearchWidget.cfpoq");
    setFormText();
    slotRefresh();
    connect(form->getCell("butSearch"),SIGNAL(signalPress()),this,SLOT(slotSearch()));
    connect(form->getCell("butCancel"),SIGNAL(signalPress()),this,SLOT(reject()));
    LayoutToForm* ltf = new LayoutToForm;
    ltf->addFormData(form);
    setLayout(ltf);

    QPalette pal;
    QColor color(255,255,185);
    pal.setColor(backgroundRole(),color);
    setPalette(pal);
}

SearchWidget::~SearchWidget(){
    delete form;
}

void SearchWidget::setFormText(){
    form->getCell("lblBookName")->setValue(tr("Title"));
    form->getCell("lblCategory")->setValue(tr("Category"));
    form->getCell("lblSubcategory")->setValue(tr("Subcategory"));
    form->getCell("lblTypeBook")->setValue(tr("Book type"));
    form->getCell("lblAuthor")->setValue(tr("Authors"));
    form->getCell("lblPublicationName")->setValue(tr("Publication Home"));
    form->getCell("lblPublicationCity")->setValue(tr("City"));
    form->getCell("lblPublicationYear")->setValue(tr("Year"));

    form->getCell("butSearch")->setValue(tr("Search"));
    form->getCell("butCancel")->setValue(tr("Cancel"));
}

void SearchWidget::slotRefresh(){
    QStringList compList;
    QStringList tempList;
    compList = db->selectQueryColumnAsList("SELECT type FROM tableBooksTypes ORDER BY type ASC");
    form->getCell("fldTypeBook")->setList(compList);
    compList = db->selectQueryColumnAsList("SELECT DISTINCT category FROM tableBooks ORDER BY category ASC");
    form->getCell("fldCategory")->setList(compList);

    compList = db->selectQueryColumnAsList("SELECT DISTINCT publicationName FROM tableBooks ORDER BY publicationName ASC");
    compList.removeAll("");
    form->getCell("fldPublicationName")->setList(compList);

    compList = db->selectQueryColumnAsList("SELECT DISTINCT publicationCity FROM tableBooks ORDER BY publicationCity ASC");
    form->getCell("fldPublicationCity")->setList(compList);
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


void SearchWidget::slotSearch(){
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

    if (form->getValue("fldPublicationName")!=""){
        if (whereStr!="") whereStr=whereStr+" AND ";
        QStringList lst = form->getValue("fldPublicationName").split("; ");

        for (int i=0;i<lst.count();i++){
            if (i==0){
                whereStr=whereStr+"(publicationName LIKE \"%"+lst[i]+"%\"";
            }else{
                whereStr=whereStr+" OR publicationName LIKE \"%"+lst[i]+"%\"";
            }
        }
        whereStr=whereStr+")";
    }

    if (form->getValue("fldPublicationCity")!=""){
        if (whereStr!="") whereStr=whereStr+" AND ";
        whereStr=whereStr+"publicationCity LIKE \"%"+form->getValue("fldPublicationCity")+"%\"";
    }

    if (form->getValue("fldPublicationYear")!=""){
        if (whereStr!="") whereStr=whereStr+" AND ";
        whereStr=whereStr+"publicationYear LIKE \"%"+form->getValue("fldPublicationYear")+"%\"";
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

    result = data;
    accept();
}
