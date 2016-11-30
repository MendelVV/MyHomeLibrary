#ifndef LIBRARYCLASS_H
#define LIBRARYCLASS_H

#include "bookclass.h"
#include "settingsbooksclass.h"

class LibraryClass//класс библиотеки
{
public:
    LibraryClass(QVector<BookClass*> vec);
    void addBook(BookClass* book);
    void removeBook(BookClass* book);
    BookClass* getBook(int n);
    int count();

    void setSetting(SettingsBooksClass* set);
    SettingsBooksClass* getSetting();

protected:
    QVector<BookClass*> books;
    SettingsBooksClass* setting;
};

#endif // LIBRARYCLASS_H
