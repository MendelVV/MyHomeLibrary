#ifndef SQLCLASS_H
#define SQLCLASS_H

#include <QObject>
#include <QtSql>
#include <QString>
#include <QMap>
#include <QDebug>
#include "sqlcursor.h"

class SQLClass : public QObject
{
    Q_OBJECT
public:
    explicit SQLClass(QString dbNm, QObject *parent = 0);

    void setDbName(QString dbNm);
    QString getDbName();

    void create();
    void createTable(QString tableName, QMap<QString, QString> map, QVector<QString> vec);
    //создаем таблицу по словарю. индекс - название столбца. значение - тип столбца
    void insertData(QString tableName, SQLCursor* cursor);
    QVector<QVector<QString> > select(QString tableName, QVector<QString> cols, QString whereStr, QVector<QString> sort);
    QMap<QString, QString>  selectAsMap(QString tableName, QString colKey, QString colVal, QString whereStr);
    void updateData(QString tableName, SQLCursor* cursor, QVector<QString> whereStr);
    int selectCount(QString tableName, QString whereStr="");

    QVector<QVector<QString> > getQueryData(QString qr);

    QVector<QVector<QString> > getAllData(QString tableName, QString sortCol="");
    QVector<QString> selectColumn(QString tableName, QString columnName, QString whereStr="");
    QVector<QString> selectQueryColumn(QString qr);
    QStringList selectQueryColumnAsList(QString qr);

    void deleteWhereData(QString tableName, QString whereStr);

//    void createTableFunction();
    void clearData(QString tableName);
    void dropDatabase(QString dbNm);
    bool isDatabase();

    SQLCursor* getCursor(QString tableName);

    QString lastError;
protected:
    //==================================================
    void insertData(QString tableName, QVector<QString> lst);
    void updateData(QString tableName, QVector<QString> cols, QVector<QString> vec,QString whereStr);
    QVector<QVector<QString> > getWhereData(QString tableName, QString whereStr, QString sortCol="");


//===============================================================================
    QSqlDatabase db;

    QString dbName;
signals:
public slots:

};

#endif // SQLCLASS_H
