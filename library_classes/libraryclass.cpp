#include "libraryclass.h"

LibraryClass::LibraryClass(QVector<BookClass*> vec)
{
    books = vec;
    setting = 0;
}

void LibraryClass::addBook(BookClass* book){
    books<<book;
}

void LibraryClass::removeBook(BookClass* book){
    books.removeAll(book);
}

BookClass* LibraryClass::getBook(int n){
    if (n<books.count()){
        return books[n];
    }else{
        return 0;
    }
}

int LibraryClass::count(){
    return books.count();
}

void LibraryClass::setSetting(SettingsBooksClass* set){
    setting = set;
}

SettingsBooksClass* LibraryClass::getSetting(){
    return setting;
}
