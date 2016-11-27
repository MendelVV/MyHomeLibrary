#ifndef BIBLIOGRAFYCLASS_H
#define BIBLIOGRAFYCLASS_H

#include <QString>
#include <QMap>

class BibliografyClass//класс библиграфического списка
{
public:
    BibliografyClass(QString cd, QString tp, QString val, QString nt);
    void setValue(QString);
    void setType(QString);
    void setNote(QString);

    QString getCode();
    QString getValue();
    QString getType();
    QString getNote();
    //строки имеют типизированный вид. напрмер: "author/ bookName: publicationYear, - pages."
protected:
    QString code;
    QString value;
    QString type;
    QString note;
};

#endif // BIBLIOGRAFYCLASS_H
