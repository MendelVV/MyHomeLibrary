#include "librarywindow.h"

LibraryWindow::LibraryWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowTitle("My home's library 1.0.1");
//    QPixmap pxmLib(":/resource/library.png");
//    setWindowIcon(pxmLib);
    x =((double)GetSystemMetrics(SM_CXSCREEN))/100;
    y =((double)GetSystemMetrics(SM_CYSCREEN))/100;
    //список всех книг
    //это таблица
    //сначала считываем данные из базы

    //пытаемся считать файл настроек
    //если ничего не получилось то создаем библиотеку
    //
    db=0;
    readData();
    QGridLayout* layout = new QGridLayout;
    layout->setMargin(1);
    layout->setSpacing(0);
    tableBooks = new BooksTable(data);
    connect(tableBooks,SIGNAL(signalOpenBook(QString)),this,SLOT(slotOpenBook(QString)));
    connect(tableBooks,SIGNAL(signalOpenBookFile(QString)),this,SLOT(slotOpenBookFile(QString)));
    tableBooks->setMinimumWidth(82*x);
//    tableBooks->setMinimumSize(82*x,88*y-38);
    layout->addWidget(tableBooks,0,0,2,1);

    filter = new FilterWidget(db, tableBooks);
    filter->setMinimumSize(17.5*x,77*y);
    layout->addWidget(filter,0,1,Qt::AlignTop);
    connect(filter,SIGNAL(signalFilter(QVector<QVector<QString> >)),tableBooks,SLOT(slotRefresh(QVector<QVector<QString> >)));
    connect(tableBooks,SIGNAL(signalSort(QString)),filter,SLOT(slotFilter(QString)));

    formInf = new FormPlusData;
    formInf->readFormPlusData(":/resource/FormInformation.cfpoq");
    LayoutToForm* ltf = new LayoutToForm;
    ltf->addFormData(formInf);
  //  ltf->setMargin(0);
    ScrollWidget* scr = new ScrollWidget(ltf);
    scr->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scr->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scr->setFixedHeight(11*y-38);
    scr->setMidLineWidth(17.5*x);
    layout->addWidget(scr,1,1);
    connect(tableBooks,SIGNAL(signalSelected(int)),this,SLOT(slotSelectedCount(int)));

    QWidget* wgt = new QWidget;

    wgt->setLayout(layout);

/*    QScrollArea* sc = new QScrollArea;
    sc->setWidget(wgt);
    setCentralWidget(sc);*/
    setCentralWidget(wgt);

    setActMenu();

    QMenu* menu = new QMenu("Меню");
    menu->addAction(actSelect);
    menu->addAction(actSave);
    menu->addSeparator();
    menu->addAction(actExit);
    menuBar()->addMenu(menu);

    QMenu* menuFunc = new QMenu("Функции");
    menuFunc->addAction(actAddBook);
    menuFunc->addAction(actSearch);
    QMenu* menuFuncLoad = new QMenu("Загрузка");
    menuFuncLoad->addAction(actLoadXml);
    menuFunc->addMenu(menuFuncLoad);
    QMenu* menuFuncUnload = new QMenu("Выгрузка");
    menuFuncUnload->addAction(actExportXml);
    menuFunc->addMenu(menuFuncUnload);
    menuFunc->addSeparator();
    menuFunc->addAction(actRemoveBook);

    menuBar()->addMenu(menuFunc);

    QMenu* menuSetting = new QMenu("Настройки");
    menuSetting->addAction(actTypesPublication);
    menuSetting->addAction(actBibliographiType);
    menuBar()->addMenu(menuSetting);

    QMenu* menuActions = new QMenu("Действия");
    menuActions->addAction(actBibliographiList);
    menuBar()->addMenu(menuActions);
    menuBar()->addAction(actAbout);
    addToolBar(Qt::TopToolBarArea,createToolBar());

    QPalette pal;
    QColor color(255,255,185);
    pal.setColor(backgroundRole(),color);
    setPalette(pal);
}

void LibraryWindow::readData(){
    QVector<BookClass*> vecBooks;
    lib = new LibraryClass(vecBooks);
    //здесь считываем файл настроек
    QString path=QCoreApplication::applicationDirPath();
    QString fname = path+"/setting.data";//имя файла настроек
    QFile file(fname);
    SettingsBooksClass* setting = new SettingsBooksClass;
    if (file.exists()){
        //если файл есть, то считываем его и запоминаем настройки
        file.open(QIODevice::ReadOnly);
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_5_4);
        stream>>*setting;
        QString strDir = setting->getDir();
        QString strDbName = setting->getDbName();
        if (strDir.indexOf("/")==0){
            setting->setDir(path+strDir);
        }
        if (strDbName.indexOf("/")==0){
            setting->setDbName(path+strDbName);
        }
        file.close();
    }else{
        //если нет файла то создаем и его и саму систему библиотеки
        //либо с нуля либо предлагаем выбрать базу данных и дирректорию данных
        //создаем диалог с выбором способа создания проекта
        DialogCreateLibrary* dlg = new DialogCreateLibrary;
        file.open(QIODevice::WriteOnly);
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_5_4);
        if (dlg->exec()==QDialog::Accepted){
            //создаем бд и каталог для хранения книг
            //и сам файл настроек
            slotCreateLibrary();
            setting->setDbName("/db_library.sqlite");
            //нужно создать дирректорию
            QDir dir(path+"/books");
            if (!dir.exists()){
                dir.mkdir(path+"/books");
            }
            setting->setDir("/books");
        }else{
            //создаем файл и пишем в него пустоту
            setting->setDir("");
            setting->setDbName("");
        }
        stream<<*setting;
        setting->setDir(path+setting->getDir());
        setting->setDbName(path+setting->getDbName());
        file.close();
        delete dlg;
    }
    lib->setSetting(setting);
    if (setting->getDir()=="" || setting->getDbName()==""){
        DialogCreateLibrary* dlg = new DialogCreateLibrary;
        file.open(QIODevice::WriteOnly);
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_5_4);
        if (dlg->exec()==QDialog::Accepted){
            //создаем бд и каталог для хранения книг
            //и сам файл настроек

            slotCreateLibrary();
            setting->setDbName("/db_library.sqlite");
            //нужно создать дирректорию
            QDir dir(path+"/books");
            if (!dir.exists()){
                dir.mkdir(path+"/books");
            }
            setting->setDir("/books");
        }else{
            //создаем файл и пишем в него пустоту
            setting->setDir("");
            setting->setDbName("");
        }
        stream<<*setting;
        setting->setDir(path+setting->getDir());
        setting->setDbName(path+setting->getDbName());
        file.close();
        delete dlg;

        return;
       //если чтото пусто в настройках то закончиливеселье
    }
    if (db==0){
        db = new SQLClass(setting->getDbName());
    }
    QDir dir(setting->getDir());
    if (!dir.exists()){//если нет такой дирректории то мы ее создадим
        dir.mkdir(setting->getDir());
    }
    //подгружаем все данные
    //запрос:
    QString qr = "SELECT code, category, subcategory, bookName, authors FROM tableBooks ORDER BY category, subcategory, bookName ASC";
    data = db->getQueryData(qr);//взяли нужные данные, но здесь у нас  часть сразу готова
    //создаем объект библиотеки, с настройками и пустым списокм книг
    //при открытии, добавлении и т.д. добвляем книгу в спиоск книг, чтобы
    //потом при сохранении знать куда вносить изменения
    //data - это сама таблица книг

    //считываем список типов изданий и сохраняем его в настройки
    QVector<QString> vecTypes = db->selectColumn("tableBooksTypes","type");
    lib->getSetting()->setTypes(vecTypes);
}

void LibraryWindow::setActMenu(){
    actSelect = new QAction("Выбрать библиотеку",0);
    connect(actSelect,SIGNAL(triggered(bool)),this,SLOT(slotSelect()));

    actSave = new QAction("Сохранить",0);
    connect(actSave,SIGNAL(triggered(bool)),this,SLOT(slotSave()));

    actExit = new QAction("Выйти",0);
    connect(actExit,SIGNAL(triggered(bool)),this,SLOT(close()));

    actLoadXml = new QAction("Загрузить XML",0);
    connect(actLoadXml,SIGNAL(triggered(bool)),this,SLOT(slotLoadXML()));

    actExportXml = new QAction("Выгрузить XML",0);
    connect(actExportXml,SIGNAL(triggered(bool)),this,SLOT(slotExportXML()));

    actAddBook = new QAction("Добавить книгу",0);
    connect(actAddBook,SIGNAL(triggered(bool)),this,SLOT(slotAddBook()));

    actSearch = new QAction("Найти книгу",0);
    connect(actSearch,SIGNAL(triggered(bool)),this,SLOT(slotSearch()));

    actRemoveBook = new QAction("Удалить книгу",0);
    connect(actRemoveBook,SIGNAL(triggered(bool)),this,SLOT(slotRemoveBook()));

    actTypesPublication = new QAction("Типы изданий",0);
    connect(actTypesPublication,SIGNAL(triggered(bool)),this,SLOT(slotTypesPublication()));

    actBibliographiList = new QAction("Библиографический список",0);
    connect(actBibliographiList,SIGNAL(triggered(bool)),this,SLOT(slotBibliografyList()));

    actBibliographiType = new QAction("Оформление библиографического списка",0);
    connect(actBibliographiType,SIGNAL(triggered(bool)),this,SLOT(slotBibliografyType()));

    actAbout = new QAction("О программе",0);
    connect(actAbout,SIGNAL(triggered(bool)),this,SLOT(slotAbout()));
}

QToolBar* LibraryWindow::createToolBar(){
    QToolBar* toolBar = new QToolBar("Инструменты",this);
    toolBar->setMovable(false);
    QPixmap pxmSave(":/resource/save.png");
    toolBar->addAction(pxmSave,"Сохранить",this,SLOT(slotSave()));
    toolBar->addSeparator();

    QPixmap pxmSearch(":/resource/search.png");
    toolBar->addAction(pxmSearch,"Найти книгу",this,SLOT(slotSearch()));
    toolBar->addSeparator();

    QPixmap pxmAddBook(":/resource/addBook.png");
    toolBar->addAction(pxmAddBook,"Добавить книгу",this,SLOT(slotAddBook()));

    toolBar->addSeparator();

    QPixmap pxmRemoveBook(":/resource/removeBook.png");
    toolBar->addAction(pxmRemoveBook,"Удалить книгу",this,SLOT(slotRemoveBook()));

    toolBar->setIconSize(QSize(32,32));
    return toolBar;
}

BookClass* LibraryWindow::readBook(QString code){
    QString qr = "SELECT * FROM tableBooks WHERE code='"+code+"';";
    QVector<QVector<QString> > vec = db->getQueryData(qr);
    BookClass* book = new BookClass;
    book->setCode(vec[0][0]);
    book->setBookName(vec[0][1]);
    book->setCategory(vec[0][2]);
    book->setSubcategory(vec[0][3]);
    book->setPublicationYear(vec[0][4]);
    book->setPublicationName(vec[0][5]);
    book->setPublicationCity(vec[0][6]);
    book->setBookType(vec[0][7]);
    book->setFileName(vec[0][8]);
    book->setAuthors(vec[0][9]);
    book->setPages(vec[0][10]);
    return book;
}

void LibraryWindow::slotSelect(){
    //выбираем файл и папку библиотеки

    DialogSelectLibrary* dlg = new DialogSelectLibrary(lib->getSetting(),this);
    dlg->setWindowTitle("Выбор библиотеки");
    if (dlg->exec()==QDialog::Accepted){
        QString path=QCoreApplication::applicationDirPath();
        QString fname = path+"/setting.data";//имя файла настроек
        QFile file(fname);
        SettingsBooksClass* setting = lib->getSetting();
        if (dlg->form->getValue("fldLibrary").indexOf(path)==0){
            setting->setDbName(dlg->form->getValue("fldLibrary").replace(path,""));
        }else{
            setting->setDbName(dlg->form->getValue("fldLibrary"));
        }
        if (dlg->form->getValue("fldDir").indexOf(path)==0){
            setting->setDir(dlg->form->getValue("fldDir").replace(path,""));
        }else{
            setting->setDir(dlg->form->getValue("fldDir"));
        }

        file.open(QIODevice::WriteOnly);
        QDataStream stream(&file);
        stream.setVersion(QDataStream::Qt_5_4);
        //нужно создать дирректорию
        QDir dir(setting->getDir());
        if (!dir.exists()){
            dir.mkdir(setting->getDir());
        }
        stream<<*setting;
        file.close();
        setting->setDbName(dlg->form->getValue("fldLibrary"));
        setting->setDir(dlg->form->getValue("fldDir"));

        db->setDbName(setting->getDbName());
        filter->slotFilter();
        filter->slotRefresh();
    }
    delete dlg;
}

void LibraryWindow::slotSave(){
    //лупим в бд все что есть в lib
    //но в lib только для обновления, не для добавление.добавляем сразу
    SQLCursor* cur = db->getCursor("tableBooks");
    //взяли курсор таблицы
    QVector<QString> vecWhere;
    int n = lib->count();
    QVector<QString> line;
    for (int i=0;i<n;i++){
        line.clear();
        BookClass* book = lib->getBook(i);
        line<<book->getCode()<<book->getCategory()<<book->getSubcategory()<<book->getPublicationYear();
        line<<book->getPublicationName()<<book->getPublicationCity()<<book->getBookType()<<book->getFileName();
        int m = book->getAuthors().count();
        QString authors="";
        for (int j=0;j<m;j++){
            if (j>0){
                authors=authors+"; "+book->getAuthors()[j];
            }else{
                authors=book->getAuthors()[j];
            }
        }
        line<<authors<<book->getPages();
        QString whereStr = "code="+book->getCode();
        vecWhere<<whereStr;
        cur->putLine(line);
    }
    db->updateData("tableBooks",cur,vecWhere);
    delete cur;
}

void LibraryWindow::slotAddBook(){
    BookClass* book = new BookClass;
    BookView* bookView = new BookView(book, db, lib->getSetting(), this);
    connect(bookView,SIGNAL(signalNew(BookClass*)),this,SLOT(slotNewBook(BookClass*)));
    bookView->move(20*x,20*y);
    bookView->show();

}

void LibraryWindow::slotSearch(){
    SearchWidget* shw = new SearchWidget(db,this);
    shw->setWindowTitle("Поиск книг");
    if (shw->exec()==QDialog::Accepted){
        tableBooks->slotRefresh(shw->result);
    }
    delete shw;
}

void LibraryWindow::slotRemoveBook(){
    //удаляем книгу
    //из базы, из таблицы, из выбранных, из каталога файлов
    QVector<QString> codes = tableBooks->getSelected();
    //лупим диалог об удалении
    if (codes.count()==0) return;
    FormPlusData* form = new FormPlusData;

    QString str = "Вы уверены, что хотите удалить выбранные книги ("+QString::number(codes.count())+") ?";
    CellPlusClass* cell;
    cell = new CellPlusClass("lblText", "MultyLabel", str, 0, 0, 14, 5);
    cell->setMergeColumn(2);
    form->addCell(cell);

    cell = new CellPlusClass("butOk", "Button", "Да", 1, 0, 7, 3);
    form->addCell(cell);

    cell = new CellPlusClass("butCancel", "Button", "Нет", 1, 1, 7, 3);
    form->addCell(cell);
    DialogInForm* dlg = new DialogInForm(form,this);

    if (dlg->exec()==QDialog::Accepted){
        //удаляем
        QString whereStr="";
        int n = codes.count();
        QVector<QVector<QString> > vecFiles;
        QVector<QString> cols;
        cols<<"code"<<"fileName";
        for (int i=0;i<n;i++){
            //собираем данные по 50 книг чтобы не делать слишком длинных запросов
            if (i%50!=0){
                whereStr=whereStr+" OR code=\""+codes[i]+"\"";
            }else{
                if (i>0){
                    QVector<QVector<QString> > vec = db->select("tableBooks",cols,whereStr,cols);
                    vecFiles<<vec;
                    db->deleteWhereData("tableBooks",whereStr);
                }
                whereStr="code=\""+codes[i]+"\"";
            }
        }

        QVector<QVector<QString> > vec = db->select("tableBooks",cols,whereStr,cols);
        vecFiles<<vec;
        db->deleteWhereData("tableBooks",whereStr);
        tableBooks->deselectAll();

        //обновляем фильтр
        filter->slotRefresh();
        filter->slotFilter();
        //удаляем сам файл книги
        n = vecFiles.count();//на всякий случай
        QString path = lib->getSetting()->getDir();
        for (int i=0;i<n;i++){
            QFile fileBook(path+"/"+vecFiles[i][1]);
            fileBook.remove();
        }
    }
    delete dlg;
}

void LibraryWindow::slotLoadXML(){
    QString str = QFileDialog::getOpenFileName(this,"Выберите xml файл","","");
    if (str.right(4)==".xml"){
        QVector<BookClass*> books = readXML(str);
        //считали xml файл и теперь имеем вектор книг
        //проверяем какие есть
        SQLCursor* cur = db->getCursor("tableBooks");
        QVector<QString> line;
        QVector<QString> vecCode = db->selectColumn("tableBooks","code");
        int n = books.count();
        //qDebug()<<"books.count() ="<<n<<vecCode.count();
        int dubels = 0;
        for (int i=0;i<n;i++){
            BookClass* book = books[i];
            if (vecCode.contains(book->getCode())){
                dubels++;
            }else{
                line.clear();
                line<<book->getCode()<<book->getBookName()<<book->getCategory()<<book->getSubcategory();
                line<<book->getPublicationYear()<<book->getPublicationName()<<book->getPublicationCity();
                line<<book->getBookType()<<book->getFileName()<<book->getAuthors()<<book->getPages();
                cur->putLine(line);
                vecCode<<book->getCode();
            }
        }
        if (dubels>0){
            QMessageBox* msb = new QMessageBox;
            msb->setWindowTitle("Совпадения!");
            msb->setText("Найдено "+QString::number(dubels)+" совпадений. Будет загружено "+QString::number(n-dubels)+
                         " книг.");
            msb->show();
        }

        db->insertData("tableBooks",cur);
        QString qr = "SELECT code, category, subcategory, bookName, authors FROM tableBooks ORDER BY category, subcategory, bookName ASC";
        data = db->getQueryData(qr);//взяли нужные данные, но здесь у нас  часть сразу готова
        tableBooks->slotRefresh(data);
        filter->slotRefresh();
    }else{
        QMessageBox* msb = new QMessageBox;
        msb->setWindowTitle("Ошибка!");
        msb->setText("Файл не соответствует.");
        msb->show();
    }
}

void LibraryWindow::slotExportXML(){
    //берем все выделенные книги
    QVector<QString> codes = tableBooks->getSelected();
    //лупим диалог об удалении
    if (codes.count()==0) return;
    QString str = QFileDialog::getExistingDirectory(this, "Выберите дирректорию В которую экспортировать книги");
    if (str!=""){
        //сохраняем файл

        //считываем все книги по кодам
        QVector<BookClass*> vecB;
        int n = codes.count();
        QDir dirB(str+"/books");
        if (!dirB.exists()){
            dirB.mkdir(str+"/books");
        }
        QString path = lib->getSetting()->getDir()+"/";
        for (int i=0;i<n;i++){
            BookClass* book = readBook(codes[i]);
            vecB<<book;
            QFile file(path+book->getFileName());
            file.copy(str+"/books/"+book->getFileName());
        }
        //сохраняем xml
        writeXML(str+"/books.xml",vecB);


    }
}

void LibraryWindow::slotCreateLibrary(){
//список всех таблиц: tableBooks; tableBooksTypes; tableBibliografy
    //создаем все таблицы
    QString path=QCoreApplication::applicationDirPath();
    db = new SQLClass(path+"/db_library.sqlite");//подключились к бд
    //возможен вариант с выбором источника данных
    //создаем таблицы
    QMap<QString, QString> map;
    QVector<QString> vec;
    //таблица книг
    map["code"]="VARCHAR(255)";
    vec<<"code";
    map["bookName"]="VARCHAR(255)";
    vec<<"bookName";
    map["category"]="VARCHAR(255)";//категория
    vec<<"category";
    map["subcategory"]="VARCHAR(255)";//список подкатегорий
    vec<<"subcategory";
    map["publicationYear"]="VARCHAR(255)";
    vec<<"publicationYear";
    map["publicationName"]="VARCHAR(255)";
    vec<<"publicationName";
    map["publicationCity"]="VARCHAR(255)";
    vec<<"publicationCity";
    map["bookType"]="VARCHAR(255)";
    vec<<"bookType";
    map["fileName"]="VARCHAR(255)";
    vec<<"fileName";
    map["authors"]="VARCHAR(255)";//список авторов
    vec<<"authors";
    map["pages"]="VARCHAR(255)";
    vec<<"pages";
    db->createTable("tableBooks",map,vec);
    map.clear();
    vec.clear();
    //типы изданий
    map["code"]="INT(11)";
    vec<<"code";
    map["type"]="VARCHAR(255)";
    vec<<"type";
    db->createTable("tableBooksTypes",map,vec);
    map.clear();
    vec.clear();
    //библиография
    map["code"]="INT(11)";//обычный код
    vec<<"code";
    map["type"]="VARCHAR(255)";//тип издания для которого строка библиографии
    vec<<"type";
    map["value"]="VARCHAR(512)";//Значение строки
    vec<<"value";
    map["note"]="VARCHAR(512)";//примечание
    vec<<"note";
    map["selected"]="INT(1)";//выьрано или нет
    vec<<"selected";
    db->createTable("tableBibliografy",map,vec);
    QVector<QString> line;
    SQLCursor* cur = new SQLCursor;
    cur->putColumn("code",SQLCursor::INT);
    cur->putColumn("type",SQLCursor::VARCHAR);
    cur->putColumn("value",SQLCursor::VARCHAR);
    cur->putColumn("note",SQLCursor::VARCHAR);
    cur->putColumn("selected",SQLCursor::INT);
    QString str="author%% %%bookName%%/ %%authors%%.- %%publicationCity%%: %%publicationName%%, %%publicationYear%%.- %%pages%% с.%%";
    line<<"1"<<"Общий"<<str<<"Стандартное оформление"<<"1";
    cur->putLine(line);
    db->insertData("tableBibliografy",cur);
    delete cur;
    //стандартные данные добавляем
    cur = new SQLCursor;
    cur->putColumn("code",SQLCursor::INT);
    cur->putColumn("type",SQLCursor::VARCHAR);
    QStringList lst;
    lst<<"Журнал"<<"Монография"<<"Научная статья"<<"Научно-популярное пособие"<<"Научное пособие"<<"Учебное пособие"<<"Художественная литература";
    int n = lst.count();
    for (int i=0;i<n;i++){
        line.clear();
        line<<QString::number(i+1)<<lst[i];
        cur->putLine(line);
    }
    db->insertData("tableBooksTypes",cur);
    delete cur;
}

void LibraryWindow::slotTypesPublication(){
    DialogTypesBook* dlg = new DialogTypesBook(db,this);
    if (dlg->exec()==QDialog::Accepted){
        filter->slotRefresh();
    }
    delete dlg;
}

void LibraryWindow::slotSelectedCount(int ct){
    formInf->getCell("fldSelectCount")->setValue("Выбрано: "+QString::number(ct));
    formInf->getCell("fldSelectCount")->changeValueWidget();
}

void LibraryWindow::slotBibliografyType(){
    BibliografyList* bl = new BibliografyList(db, this);
    bl->move(20*x,20*y);
    bl->show();

}

void LibraryWindow::slotBibliografyList(){
    //берем те списки литературы котрые выбраны
    QString whereStr = "selected=1";
    QMap<QString, QString> mapBib = db->selectAsMap("tableBibliografy","type","value",whereStr);
    //итого имеем словарь библиографических описаний
    //идем по всем выбранным книжкам
    if (!mapBib.contains("Общий")){
        QMessageBox* msb = new QMessageBox(this);
        msb->setWindowTitle("Ошибка!");
        msb->setText("Должен быть указан общий тип оформления списка литературы!");
        msb->show();
        return;
    }
    QVector<QString> codes = tableBooks->getSelected();
    int n = codes.count();
    QVector<QString> cols;
    cols<<"authors"<<"publicationYear"<<"publicationCity"<<"bookName"<<"publicationName"<<"pages"<<"bookType";
    QVector<QString> sort;
    QVector<QVector<QString> > vecBooks;

    for (int i=0;i<n;i++){
        //собираем данные по 50 книг чтобы не делать слишком длинных запросов
        if (i%50!=0){
            whereStr=whereStr+" OR code=\""+codes[i]+"\"";
        }else{
            if (i>0){
                QVector<QVector<QString> > vecB = db->select("tableBooks",cols,whereStr,sort);
                vecBooks<<vecB;
            }
            whereStr="code=\""+codes[i]+"\"";
        }
    }
    QVector<QVector<QString> > vecB = db->select("tableBooks",cols,whereStr,sort);
    vecBooks<<vecB;
    //считали все книги в вектор книг
    n = vecBooks.count();
    QString strBib="";

    for (int i=0;i<n;i++){
        //для каждой книги
        QMap<QString, QString> map;//словарь что на что менять
        QStringList lstAuthors = vecBooks[i][0].split("; ");
        map["author"]=lstAuthors[0];//"Автор";
        for (int j=0;j<lstAuthors.count();j++){
            QStringList lstTemp = lstAuthors[j].split(" ");
            QString strA = lstTemp[0];
            lstTemp.removeAt(0);
            lstTemp<<strA;
            strA = lstTemp.join(" ");
            lstAuthors[j]=strA;
        }
        map["authors"]=lstAuthors.join(", ");//"Авторы";
        map["publicationYear"]=vecBooks[i][1];//"Год издания";
        map["publicationCity"]=vecBooks[i][2];//"Город";
        map["bookName"]=vecBooks[i][3];//"Название";
        map["publicationName"]=vecBooks[i][4];//"Издательство";
        map["pages"]=vecBooks[i][5];//"Страницы";
        map["bookType"]=vecBooks[i][6];//"Тип издания";
        QString res="";
        if (mapBib.contains(vecBooks[i][6])){
            //идем по соответствующему типу
            QStringList list = mapBib[vecBooks[i][6]].split("%%");
            int m = list.count();//всего элементов
            for (int j=0;j<m;j++){
                if (map.contains(list[j])){
                    res=res+map[list[j]];
                }else{
                    res=res+list[j];
                }
            }
        }else{
            //идем по общему типу
            QStringList list = mapBib["Общий"].split("%%");
            int m = list.count();//всего элементов
            for (int j=0;j<m;j++){
                if (map.contains(list[j])){
                    res=res+map[list[j]];
                }else{
                    res=res+list[j];
                }
            }
        }
        strBib=strBib+res+"\n";
    }
    QTextEdit* textBib = new QTextEdit;
    QPixmap pxmLib(":/resource/library.png");
    textBib->setWindowIcon(pxmLib);
    textBib->setWindowTitle("Список литературы");
    textBib->setPlainText(strBib);
    textBib->setFixedSize(50*x,30*y);
    textBib->move(20*x,20*y);
    textBib->show();
}

void LibraryWindow::slotNewBook(BookClass *book){
    //собираем все по частям. сейчас в объекте много информации которая не обработана
    //нужно перевести все списки или нет
    //пусть лучше данные хранятся как есть
    SQLCursor* cur = db->getCursor("tableBooks");
    QVector<QString> line;
    line<<book->getCode()<<book->getBookName()<<book->getCategory()<<book->getSubcategory();
    line<<book->getPublicationYear()<<book->getPublicationName()<<book->getPublicationCity();
    line<<book->getBookType()<<book->getFileName()<<book->getAuthors()<<book->getPages();
    cur->putLine(line);
    db->insertData("tableBooks",cur);
    delete cur;

    QString qr = "SELECT code, category, subcategory, bookName, authors FROM tableBooks ORDER BY category, subcategory, bookName ASC";
    data = db->getQueryData(qr);//взяли нужные данные, но здесь у нас  часть сразу готова
    tableBooks->slotRefresh(data);
}

void LibraryWindow::slotSaveBook(BookClass *book,QString oldCode){
    //собираем все по частям. сейчас в объекте много информации которая не обработана
    //нужно перевести все списки или нет
    //пусть лучше данные хранятся как есть
    SQLCursor* cur = db->getCursor("tableBooks");
    QVector<QString> line;
    line<<book->getCode()<<book->getBookName()<<book->getCategory()<<book->getSubcategory();
    line<<book->getPublicationYear()<<book->getPublicationName()<<book->getPublicationCity();
    line<<book->getBookType()<<book->getFileName()<<book->getAuthors()<<book->getPages();
    cur->putLine(line);
    QVector<QString> vecWhere;
    vecWhere<<"code='"+oldCode+"'";
    db->updateData("tableBooks",cur,vecWhere);
    delete cur;
    filter->slotFilter();
/*    QString qr = "SELECT code, category, subcategory, bookName, authors FROM tableBooks ORDER BY category, subcategory, bookName ASC";
    data = db->getQueryData(qr);//взяли нужные данные, но здесь у нас  часть сразу готова

//    tableBooks->slotRefresh(data);*/
}

void LibraryWindow::slotOpenBook(QString code){
    BookClass* book = readBook(code);
    BookView* bookView = new BookView(book,db,lib->getSetting(),this);
    connect(bookView,SIGNAL(signalSave(BookClass*,QString)),this,SLOT(slotSaveBook(BookClass*,QString)));
    bookView->move(20*x,20*y);
    bookView->show();
}

void LibraryWindow::slotOpenBookFile(QString code){
    QVector<QString> vec = db->selectColumn("tableBooks","fileName","code='"+code+"'");
    if (vec[0]!=""){
        QString fname = lib->getSetting()->getDir()+"/"+vec[0];
        QUrl url("file:/"+fname);
        QDesktopServices::openUrl(url);
    }else{
        QMessageBox* msb = new QMessageBox(this);
        msb->setWindowTitle("Ошибка!");
        msb->setText("Не указано имя файла!");
        msb->show();
    }
}

void LibraryWindow::slotAbout(){
    QFont font("Times",11,QFont::Normal);
    QTextEdit* label = new QTextEdit("",0);

    label->setFont(font);
    label->setWindowTitle("О программе");
    label->setEnabled(false);
    QString str = "<center><font color='black' size='4'>My home library 1.0.1</font></center>";
    str = str+"<p align='justify'><font color='black'>Приложение разработано на основе библиотеки QT (версия 5.5.1) и предназначено для ведения "
            "вашей собственной домашней библиотеки. My home library 1.0.1 поддерживает хранение сведений о книгах и удобный поиск по различным критериям, "
            "формирование библиографических списков по вашему описанию, а так же выгрузку книг для обмена с другими людьми.";
    str=str+"<br><br>Авторы: Мендель В.В., Косатюк П.И.";
    str=str+"<br>Контактная информация:</font> <font color='blue'>mendel.vasilij@yandex.ru</font></p>";
    str=str+"<center>2016 г. Версия 1.0.1</center>";

    label->insertHtml(str);
    label->setFixedWidth(40*x);
    label->resize(40*x,32*y);
    label->show();
}
