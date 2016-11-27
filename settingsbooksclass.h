#ifndef SETTINGSBOOKSCLASS_H
#define SETTINGSBOOKSCLASS_H

#include <QString>
#include <QVector>
#include "bookclass.h"
#include <QtXml>

class SettingsBooksClass//класс настроек.
        //содержит список типов книг, список библиографических списков
{
public:
    SettingsBooksClass();
    void setDbName(QString str);
    QString getDbName();
    void setDir(QString str);
    QString getDir();
    void setData(QString nm, QString val);
    QString getData(QString nm);

    void addType(QString str);
    void setTypes(QVector<QString> vec);
    void removeType(QString str);
    QVector<QString> getTypesBooks();

    friend QDataStream & operator << (QDataStream & out, const SettingsBooksClass &setting);
    friend QDataStream & operator >> (QDataStream & out, SettingsBooksClass &setting);
protected:
    QVector<QString> typesBooks;//возможные типы книг
    QString dbName;//имя базы данных библиотеки
    QString dirBooks;//дирректория в которой лежат книги библиотеки
    QMap<QString,QString> mapData;//содержит какие то еще настройки
//    QVector<BibliografyClass*> bibliografics;//варианты создание библиографической записи?
//список лежит в бд
};

void writeXML(QString fileName, QVector<BookClass*>);
QVector<BookClass*> readXML(QString fileName);

#endif // SETTINGSBOOKSCLASS_H
