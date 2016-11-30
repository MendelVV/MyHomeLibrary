#ifndef BOOKCLASS_H
#define BOOKCLASS_H

#include <QString>
#include <QVector>
#include <QStringList>

class BookClass
{
public:
    BookClass();
    void setBookName(QString str);
    void setCategory(QString str);
    void setSubcategory(QString str);
    void setPublicationYear(QString str);
    void setPublicationName(QString str);
    void setPublicationCity(QString str);
    void setBookType(QString str);
    void setFileName(QString str);
    void setCode(QString str);
    void setPages(QString str);
    void setAuthors(QString str);

    QString getBookName();
    QString getCategory();
    QString getSubcategory();
    QString getPublicationYear();
    QString getPublicationName();
    QString getPublicationCity();
    QString getBookType();
    QString getFileName();
    QString getCode();
    QString getPages();
    QString getAuthors();

    QString createCode();

protected:
    QString bookName;
    QString category;
    QString subcategory;
    //опубликовано
    QString publicationYear;//когда
    QString publicationName;//кем
    QString publicationCity;//в каком городе
    QString bookType;//тип книги. учебное пособие, научное пособие, и т.д.
    QString fileName;//имя файла
    QString code;//код - название_автор_автор_..._год
    QString authors;//список авторов
    QString pages;//количество страниц

};

#endif // BOOKCLASS_H
