#include "bookclass.h"

BookClass::BookClass()
{
    bookName="";
    category="";
    subcategory="";
    publicationYear="";//когда
    publicationName="";//кем
    publicationCity="";//в каком городе
    bookType="";//тип книги. учебное пособие, научное пособие, и т.д.
    fileName="";//имя файла
    code="";//код - название_автор_автор_..._год
    authors="";
    pages="";//количество страниц
}

void BookClass::setBookName(QString str){
    bookName=str;
}

void BookClass::setCategory(QString str){
    category=str;
}

void BookClass::setSubcategory(QString str){
    subcategory=str;
}

void BookClass::setPublicationYear(QString str){
    publicationYear=str;
}

void BookClass::setPublicationName(QString str){
    publicationName=str;
}

void BookClass::setPublicationCity(QString str){
    publicationCity=str;
}

void BookClass::setBookType(QString str){
    bookType=str;
}

void BookClass::setFileName(QString str){
    fileName=str;
}

void BookClass::setCode(QString str){
    code=str;
}

void BookClass::setPages(QString str){
    pages=str;
}

void BookClass::setAuthors(QString str){
    authors=str;
}

QString BookClass::getBookName(){
    return bookName;
}

QString BookClass::getCategory(){
    return category;
}

QString BookClass::getSubcategory(){
    return subcategory;
}

QString BookClass::getPublicationYear(){
    return publicationYear;
}

QString BookClass::getPublicationName(){
    return publicationName;
}

QString BookClass::getPublicationCity(){
    return publicationCity;
}

QString BookClass::getBookType(){
    return bookType;
}

QString BookClass::getFileName(){
    return fileName;
}

QString BookClass::getCode(){
    return code;
}

QString BookClass::getPages(){
    return pages;
}

QString BookClass::getAuthors(){
    return authors;
}

QString BookClass::createCode(){
    //создаем код из данных которые есть
    //название_авторавтор...автор_год
    QString str = bookName;
    QStringList lst = authors.split("; ");
    int n = lst.count();
    if (n>0) str=str+"_";
    for (int i=0;i<n;i++){
        QStringList vals = lst[i].split(" ");
        QString val = vals[0];
        str=str+val;
    }
    str=str+"_"+publicationYear;
    code=str;
    return code;
}
