#include "bookview.h"

BookView::BookView(BookClass* bk, SQLClass* dbC, SettingsBooksClass* set, QWidget *parent) :
    QMainWindow(parent)
{
    book = bk;
    db = dbC;
    setting = set;
    form = new FormPlusData;
    form->readFormPlusData(":/resource/FormBookView.cfpoq");
    QVector<QString> vecTypes = db->selectColumn("tableBooksTypes","type");
    QStringList lst;
    int n = vecTypes.count();
    for (int i=0;i<n;i++){
        lst<<vecTypes[i];
    }
    form->getCell("fldTypeBook")->setList(lst);

    isNew=false;
    if (book->getBookName()==""){
        setWindowTitle("Новая книга");
        isNew=true;
    }else{
        setWindowTitle(book->getBookName());    
        //задаем сведения о книге
        form->getCell("fldBookName")->setValue(book->getBookName());
        form->getCell("fldCategory")->setValue(book->getCategory());
        form->getCell("fldSubcategorys")->setValue(book->getSubcategory());
        form->getCell("fldTypeBook")->setValue(book->getBookType());
        form->getCell("fldAuthors")->setValue(book->getAuthors());
        form->getCell("fldPublicationName")->setValue(book->getPublicationName());
        form->getCell("fldPublicationCity")->setValue(book->getPublicationCity());
        form->getCell("fldPublicationYear")->setValue(book->getPublicationYear());
        form->getCell("fldPages")->setValue(book->getPages());
        form->getCell("fldFileName")->setValue(book->getFileName());
        oldCode = book->getCode();//запомнили старый код. пригодится при сохранении
    }
    CellPlusClass* cell;
    //добавляем варианты в comleter
    QStringList compList;
    QStringList tempList;
    compList = db->selectQueryColumnAsList("SELECT DISTINCT category FROM tableBooks ORDER BY category ASC");
    form->getCell("fldCategory")->setList(compList);
    //с автором и с подкатегориями немножко иначе
    compList.clear();
    tempList = db->selectQueryColumnAsList("SELECT DISTINCT subcategory FROM tableBooks ORDER BY subcategory ASC");
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
    form->getCell("fldSubcategory")->setList(compList);
    connect(form->getCell("fldSubcategory"),SIGNAL(signalShiftEnter()),this,SLOT(slotPlusValue()));


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
    connect(form->getCell("fldAuthor"),SIGNAL(signalShiftEnter()),this,SLOT(slotPlusValue()));
    //слоты подключаем

    cell = form->getCell("butSubcategoryPlus");
    connect(cell,SIGNAL(signalPress()),this,SLOT(slotPlusValue()));

    cell = form->getCell("butSubcategoryMinus");
    connect(cell,SIGNAL(signalPress()),this,SLOT(slotMinusValue()));

    cell = form->getCell("butAuthorPlus");
    connect(cell,SIGNAL(signalPress()),this,SLOT(slotPlusValue()));

    cell = form->getCell("butAuthorMinus");
    connect(cell,SIGNAL(signalPress()),this,SLOT(slotMinusValue()));
    //=======================================

    LayoutToForm* ltf = new LayoutToForm;
    ltf->addFormData(form);
    QWidget* wgt = new QWidget;
    wgt->setLayout(ltf);
    setCentralWidget(wgt);

    setActMenu();
    QMenu* menu = new QMenu("Меню");
    menu->addAction(actSave);
    menu->addAction(actSaveAndClose);
    menu->addSeparator();
    menu->addAction(actClose);
    menuBar()->addMenu(menu);

    QMenu* menuBook = new QMenu("Файл книги");
    menuBook->addAction(actOpenBook);
    menuBook->addAction(actSelectFile);
    menuBar()->addMenu(menuBook);

    QPalette pal;
    QColor color(234,252,250);
    pal.setColor(backgroundRole(),color);
    setPalette(pal);
}

BookView::~BookView(){
    delete form;
}

void BookView::setActMenu(){
    actSave = new QAction("Сохранить",0);
    connect(actSave,SIGNAL(triggered(bool)),this,SLOT(slotSave()));

    actSaveAndClose = new QAction("Сохранить и закрыть",0);
    connect(actSaveAndClose,SIGNAL(triggered(bool)),this,SLOT(slotSaveAndClose()));

    actClose = new QAction("Закрыть",0);
    connect(actClose,SIGNAL(triggered(bool)),this,SLOT(close()));

    actOpenBook = new QAction("Открыть книгу",0);
    connect(actOpenBook,SIGNAL(triggered(bool)),this,SLOT(slotOpenBook()));

    actSelectFile = new QAction("Выбрать файл",0);
    connect(actSelectFile,SIGNAL(triggered(bool)),this,SLOT(slotSelectFile()));
}

void BookView::slotSave(){
    if (form->getValue("fldBookName")=="" || form->getValue("fldPublicationYear")==""){
        QMessageBox* msb = new QMessageBox(this);
        msb->setWindowTitle("Ошибка!");
        msb->setText("Не указано название книги или год издания!");
        msb->show();
        return;
    }
    //все из формы загоняем в объект
    book->setBookName(form->getValue("fldBookName"));
    book->setCategory(form->getValue("fldCategory"));
    book->setSubcategory(form->getValue("fldSubcategorys"));
    book->setBookType(form->getValue("fldTypeBook"));
    book->setAuthors(form->getValue("fldAuthors"));
    book->setPublicationName(form->getValue("fldPublicationName"));
    book->setPublicationCity(form->getValue("fldPublicationCity"));
    book->setPublicationYear(form->getValue("fldPublicationYear"));
    book->setPages(form->getValue("fldPages"));
    QString code = book->createCode();//создали код книжки
    QString fname = form->getValue("fldFileName");
    if (fname!=""){
        int pos = fname.lastIndexOf(".");
        QString exp = fname.right(fname.length()-pos);
        if (book->getFileName()==""){//если небыло файла книги
            //копируем файл книги
            QFile fileBook(fname);
            fileBook.copy(setting->getDir()+"/"+code+exp);
            fileBook.close();
        }else{
            QFile fileBook(setting->getDir()+"/"+book->getFileName());
            fileBook.rename(setting->getDir()+"/"+code+exp);
            fileBook.close();
        }
        book->setFileName(code+exp);
        form->getCell("fldFileName")->setValue(book->getFileName());
        form->getCell("fldFileName")->changeValueWidget();
    }

    if (isNew){
        emit signalNew(book);
    }else{
        emit signalSave(book, oldCode);
        oldCode=book->getCode();
    }
}

void BookView::slotSaveAndClose(){
    slotSave();
    close();
}

void BookView::slotSelectFile(){
    QString str = QFileDialog::getOpenFileName(this,"Выберите файл книги","","");
    if (str!=""){
        form->getCell("fldFileName")->setValue(str);
        form->getCell("fldFileName")->changeValueWidget();
    }
}

void BookView::slotOpenBook(){
    if (book->getFileName()!=""){
        QString fname = setting->getDir()+"/"+book->getFileName();
        QUrl url("file:/"+fname);
        QDesktopServices::openUrl(url);
    }
}

void BookView::slotPlusValue(){
    CellPlusClass* cell = (CellPlusClass*) sender();
    //либо та самая кнопка либо то самое поле
    QString nm = cell->getNameCell();//имя ячейки
    QString valCell="";
    QString valsCell="";
    if (nm.contains("Subcategory")){
        valCell="fldSubcategory";
        valsCell="fldSubcategorys";
    }else if(nm.contains("Author")){
        valCell="fldAuthor";
        valsCell="fldAuthors";
    }
    //теперь добавляем значение
    QString vals = form->getValue(valsCell);
    if (vals==""){
        form->getCell(valsCell)->setValue(form->getValue(valCell));
    }else{
        form->getCell(valsCell)->setValue(vals+"; "+form->getValue(valCell));
    }
    form->getCell(valCell)->setValue("");
    form->getCell(valCell)->changeValueWidget();
    form->getCell(valsCell)->changeValueWidget();
}

void BookView::slotMinusValue(){
    CellPlusClass* cell = (CellPlusClass*) sender();
    //та самая кнопка
    QString nm = cell->getNameCell();//имя ячейки
    QString valCell="";
    QString valsCell="";
    if (nm.contains("Subcategory")){
        valCell="fldSubcategory";
        valsCell="fldSubcategorys";
    }else if(nm.contains("Author")){
        valCell="fldAuthor";
        valsCell="fldAuthors";
    }
    QString vals = form->getValue(valsCell);
    if (vals.contains("; ")){
        QString str = vals.right(vals.length()-vals.lastIndexOf("; ")-2);
        form->getCell(valCell)->setValue(str);
        vals = vals.left(vals.lastIndexOf("; "));
        form->getCell(valsCell)->setValue(vals);//тому что было задали ничего
    }else{
        form->getCell(valsCell)->setValue("");//тому что было задали ничего
        form->getCell(valCell)->setValue(vals);
    }
    form->getCell(valCell)->changeValueWidget();
    form->getCell(valsCell)->changeValueWidget();
}
