#include "settingsbooksclass.h"

SettingsBooksClass::SettingsBooksClass()
{

}

QDataStream & operator <<(QDataStream &out, const SettingsBooksClass &setting)
{
    out<<setting.dbName<<setting.dirBooks<<setting.mapData;
    return out;
}

QDataStream & operator >>(QDataStream &out, SettingsBooksClass &setting)
{
    out>>setting.dbName>>setting.dirBooks>>setting.mapData;
    return out;
}

void SettingsBooksClass::setDbName(QString str){
    dbName = str;
}

QString SettingsBooksClass::getDbName(){
    return dbName;
}

void SettingsBooksClass::setDir(QString str){
    dirBooks = str;
}

QString SettingsBooksClass::getDir(){
    return dirBooks;
}

void SettingsBooksClass::setData(QString nm, QString val){
    mapData[nm]=val;
}

QString SettingsBooksClass::getData(QString nm){
    return mapData[nm];
}

void SettingsBooksClass::addType(QString str){
    typesBooks<<str;
}

void SettingsBooksClass::setTypes(QVector<QString> vec){
    typesBooks = vec;
}

void SettingsBooksClass::removeType(QString str){
    if (typesBooks.contains(str)){
        typesBooks.removeAll(str);
    }
}

QVector<QString> SettingsBooksClass::getTypesBooks(){
    return typesBooks;
}

void writeXML(QString fileName, QVector<BookClass *> books){
    QDomDocument doc("Library");
    QDomElement domLib = doc.createElement("Library");
    int n = books.count();
    for (int i=0;i<n;i++){
        BookClass* book = books[i];
        QDomElement domBook = doc.createElement("Book");
        domBook.setAttribute("bookName",book->getBookName());
        domBook.setAttribute("category",book->getCategory());
        domBook.setAttribute("subcategory",book->getSubcategory());
        domBook.setAttribute("publicationYear",book->getPublicationYear());
        domBook.setAttribute("publicationName",book->getPublicationName());
        domBook.setAttribute("publicationCity",book->getPublicationCity());
        domBook.setAttribute("bookType",book->getBookType());
        domBook.setAttribute("fileName",book->getFileName());
        domBook.setAttribute("code",book->getCode());
        domBook.setAttribute("pages",book->getPages());
        QStringList lstAuthors = book->getAuthors().split("; ");
        for (int j=0;j<lstAuthors.count();j++){
            QDomElement domAuthor = doc.createElement("author");
            domAuthor.setAttribute("name",lstAuthors[j]);
            domBook.appendChild(domAuthor);
        }
        domLib.appendChild(domBook);
    }


    doc.appendChild(domLib);
    QFile file(fileName);

    if (file.open(QIODevice::WriteOnly)){
        QTextStream stream(&file);
        stream.setCodec(QTextCodec::codecForName("UTF-8"));
        stream<<doc.toString();
        file.close();
    }
}

QVector<BookClass*> readXML(QString fileName){
    QVector<BookClass*> vec;
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)){
        QDomDocument domDoc;
        if (domDoc.setContent(&file)){
            QDomElement domLib = domDoc.documentElement();//взяли первый елемент. главный в элемент
            if (domLib.tagName()=="Library"){
                QDomElement domBook = domLib.firstChildElement("Book");
                while (!domBook.isNull()){//пошли по всем книжкам
                    BookClass* book = new BookClass;
                    book->setBookName(domBook.attribute("bookName"));
                    book->setCategory(domBook.attribute("category"));
                    book->setSubcategory(domBook.attribute("subcategory"));
                    book->setPublicationYear(domBook.attribute("publicationYear"));
                    book->setPublicationName(domBook.attribute("publicationName"));
                    book->setPublicationCity(domBook.attribute("publicationCity"));
                    book->setBookType(domBook.attribute("bookType"));
                    book->setFileName(domBook.attribute("fileName"));
                    book->setCode(domBook.attribute("code"));
                    book->setPages(domBook.attribute("pages"));
                    QDomElement domAuthors = domBook.firstChildElement("author");
                    QString authors="";
                    while (!domAuthors.isNull()) {
                        if (authors==""){
                            authors=domAuthors.attribute("name");
                        }else{
                            authors=authors+"; "+domAuthors.attribute("name");
                        }
                        domAuthors = domAuthors.nextSiblingElement("author");
                    }
                    book->setAuthors(authors);
                    vec<<book;
                    domBook = domBook.nextSiblingElement("Book");
                }
            }
        }
    }
    return vec;
}
