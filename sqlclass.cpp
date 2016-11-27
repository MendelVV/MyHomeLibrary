#include "sqlclass.h"

SQLClass::SQLClass(QString dbNm, QObject *parent) :
    QObject(parent)
{
    dbName=dbNm;
    lastError = "not error";

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);
}

void SQLClass::setDbName(QString dbNm){
    dbName=dbNm;
    db.setDatabaseName(dbName);
}

QString SQLClass::getDbName(){
    return dbName;
}

void SQLClass::create(){
    db.setDatabaseName("test");
    if (!db.open()) {
        qDebug()<<"not opened db";
    }else {
        QSqlQuery query(db);
        query.exec("CREATE DATABASE "+dbName+";");
        qDebug()<<"created db";
        db.close();
        db.setDatabaseName(dbName);
    }
}

void SQLClass::createTable(QString tableName, QMap<QString, QString> map, QVector<QString> vec){
//готово
    if (db.open()){
 //подключились к базе данных
//        QSqlDatabase::database().transaction();//начали транзакцию
//        QString str="CREATE TABLE "+dbName+"."+tableName+" ( ";
        QString str="CREATE TABLE "+tableName+" ( ";
//добавляем столбцы
        str = str+vec[0]+" "+map[vec[0]]+" PRIMARY KEY NOT NULL, ";

        for (int i=1;i<map.count();i++){
            str = str+vec[i]+" "+map[vec[i]]+", ";
        }

        str=str.mid(0,str.length()-2);
        str=str+");";
//        str=str+QChar(10)+"ENGINE = INNODB"+QChar(10)+"CHARACTER SET cp1251"+QChar(10)+"COLLATE cp1251_general_ci;";
        QSqlQuery query;

        if (!query.exec(str)){
            qDebug()<<"not create table"<<db.lastError()<<str;
        }
//        QSqlDatabase::database().commit();//закончили транзакцию
        db.close();

    }else{
        qDebug()<<"not open"<<db.lastError();
    }
}

void SQLClass::insertData(QString tableName, QVector<QString> vec){
//готово
    if (db.open()){
 //подключились к базе данных
        bool b = true;
//        QSqlDatabase::database().transaction();//начали транзакцию
        //разумнее будет если сразу множество данных будем записывать
        //сейчас пока транзакции для примера
        QSqlQuery query;
        QString str = "INSERT INTO "+tableName+" VALUES ('"+vec[0]+"'";
        for (int i=1;i<vec.count();i++){
            str=str+", '"+vec[i]+"'";
        }
        str=str+");";
        if (!query.exec(str)){
            b=false;
            qDebug()<<"not insert data"<<db.lastError()<<str;
        }
/*        if (b){
            QSqlDatabase::database().commit();//закончили транзакцию
        }else{
            QSqlDatabase::database().rollback();//откатили изменения
        }*/
        db.close();
    }else{
        qDebug()<<"not open"<<db.lastError();
    }
}

void SQLClass::insertData(QString tableName, SQLCursor* cursor){
//готово
    if (db.open()){
 //подключились к базе данных
        QSqlQuery query;
        QString str = "INSERT INTO "+tableName+" ";
        str=str+cursor->getColumnsToString()+" VALUES";
        int n = cursor->rowCount();
        if (n==0){
            qDebug()<<"not insert rowCount=0";
            return;
        }
        for (int i=0;i<n;i++){
            if (i>0){
                str=str+", ";
            }
            str=str+cursor->getRowToString(i);
        }
        str=str+";";
        if (!query.exec(str)){
            qDebug()<<"not insert data"<<db.lastError()<<str;
        }
        db.close();
    }else{
        qDebug()<<"not open"<<db.lastError();
    }
}

QVector<QVector<QString> > SQLClass::select(QString tableName, QVector<QString> cols, QString whereStr, QVector<QString> sort){
    QVector<QVector<QString> > vec;
    if (db.open()){
 //подключились к базе данных
        QSqlQuery query;
        QString str = "SELECT ";
        int n=cols.count();
        if (n>0){
            for (int i=0;i<n;i++){
                if (i>0){
                    str=str+", ";
                }
                str = str+cols[i];
            }
        }else{
            str=str+"*";
        }
        str = str+" FROM "+tableName;
        if (whereStr!=""){
            str = str+" WHERE "+whereStr;
        }
        n = sort.count();
        if (n>0){
            str =str+" ORDER BY ";
            for (int i=0;i<n;i++){
                if (i>0){
                    str=str+",";
                }
                str = str+sort[i];
            }
            str = str+" ASC";
        }
        if (query.exec(str)){
            int i=0;
            int n = query.record().count();
            while (query.next()){
                QVector<QString> vc;
                for (int j=0;j<n;j++){
                    vc<<query.value(j).toString();//записываем всю информацию кроме порядкового номера
                }
                vec<<vc;
                i++;
            }
        }else{
            qDebug()<<"not select"<<db.lastError()<<str;
        }
        db.close();
    }else{
        qDebug()<<"not open"<<db.lastError();
    }
    return vec;
}

QMap<QString, QString> SQLClass::selectAsMap(QString tableName, QString colKey, QString colVal, QString whereStr){
    QMap<QString, QString> map;
    if (db.open()){
 //подключились к базе данных
        QSqlQuery query;
        QString str = "SELECT "+colKey+", "+colVal;
        str = str+" FROM "+tableName;
        if (whereStr!=""){
            str = str+" WHERE "+whereStr;
        }

        if (query.exec(str)){
            int i=0;
            int n = query.record().count();
            while (query.next()){
                QVector<QString> vc;
                for (int j=0;j<n;j++){
                    vc<<query.value(j).toString();//записываем всю информацию кроме порядкового номера
                }
                map[vc[0]]=vc[1];
                i++;
            }
        }else{
            qDebug()<<"not select"<<db.lastError()<<str;
        }
        db.close();
    }else{
        qDebug()<<"not open"<<db.lastError();
    }
    return map;
}

void SQLClass::updateData(QString tableName, SQLCursor* cursor, QVector<QString> whereStr){
//сразу готово
    if (db.open()){
 //подключились к базе данных
        //разумнее будет если сразу множество данных будем записывать
        //сейчас пока транзакции для примера
        QSqlQuery query;
        QString str = "";
        int n = cursor->rowCount();
        if (n==0){
            qDebug()<<"not update rowCount=0";
            return;
        }
        for (int i=0;i<n;i++){
            if (i>0){
                str = str+"\n";
            }
            str = str+"UPDATE "+tableName+" SET "+cursor->getRowForUpdate(i)+" WHERE "+whereStr[i]+";";
        }
        if (!query.exec(str)){
            qDebug()<<"not update data"<<db.lastError()<<str;
        }
        db.close();
    }else{
        qDebug()<<"not open"<<db.lastError();
    }
}

int SQLClass::selectCount(QString tableName, QString whereStr){
    int res = 0;
    if (db.open()){
 //подключились к базе данных
        //разумнее будет если сразу множество данных будем записывать
        //сейчас пока транзакции для примера
        QSqlQuery query;
        QString str = "SELECT COUNT(*) FROM "+tableName;
        if (whereStr!=""){
            str = str+" WHERE "+whereStr+";";
        }else{
            str = str+";";
        }
        if (query.exec(str)){
            if (query.next()){
                res = query.value(0).toInt();
            }
        }else{
            qDebug()<<"not select count"<<db.lastError()<<str;
        }
        db.close();
    }else{
        qDebug()<<"not open"<<db.lastError();
    }
    return res;
}

void SQLClass::updateData(QString tableName, QVector<QString> cols, QVector<QString> vec, QString whereStr){
//сразу готово
    if (db.open()){
 //подключились к базе данных
        //разумнее будет если сразу множество данных будем записывать
        //сейчас пока транзакции для примера
        QSqlQuery query;
        QString str = "UPDATE "+tableName+" SET ";
        for (int i=0;i<vec.count();i++){
            str=str+cols[i]+"='"+vec[i]+"',";
        }
        str = str.mid(0,str.length()-1);
        str = str+" WHERE "+whereStr;
        str=str+";";
//        qDebug()<<str;
        if (!query.exec(str)){
            qDebug()<<"not update data"<<db.lastError()<<str;
        }
        db.close();
    }else{
        qDebug()<<"not open"<<db.lastError();
    }
}

QVector<QVector<QString> > SQLClass::getAllData(QString tableName,QString sortCol){
//готово
    QVector<QVector<QString> > vec;
    if (db.open()){
 //подключились к базе данных
        QSqlQuery query;
        QString str = "SELECT * FROM "+tableName;
        if (sortCol!=""){
            str =str+" ORDER BY "+sortCol+" ASC;";
        }else{
            str =str+";";
        }
        if (query.exec(str)){
            int i=0;
            int n = query.record().count();
            while (query.next()){
                QVector<QString> vc;
                for (int j=0;j<n;j++){
                    vc<<query.value(j).toString();//записываем всю информацию кроме порядкового номера
                }
                vec<<vc;
                i++;
            }
        }else{
            qDebug()<<"not select"<<db.lastError()<<str;
        }
        db.close();
    }else{
        qDebug()<<"not open"<<db.lastError();
    }
    return vec;
}

QVector<QVector<QString> > SQLClass::getQueryData(QString qr){
//соазу готово
    //   qDebug()<<qr;
    QVector<QVector<QString> > vec;
    if (db.open()){
 //подключились к базе данных
        QSqlQuery query;
        if (query.exec(qr)){
            int i=0;
            int n = query.record().count();
            while (query.next()){
                QVector<QString> vc;
                for (int j=0;j<n;j++){
                    vc<<query.value(j).toString();//записываем всю информацию кроме порядкового номера
                }
                vec<<vc;
                i++;
            }
        }else{
            qDebug()<<"not select"<<db.lastError()<<qr;
        }
        db.close();
    }else{
        qDebug()<<"not open"<<db.lastError();
    }
    return vec;
}

QVector<QVector<QString> > SQLClass::getWhereData(QString tableName, QString whereStr,QString sortCol){
//готово
    QVector<QVector<QString> > vec;
    if (db.open()){
 //подключились к базе данных
        QSqlQuery query;
        QString str = "SELECT * FROM "+tableName+" WHERE "+whereStr;
        if (sortCol!=""){
            str =str+" ORDER BY "+sortCol+" ASC;";
        }else{
            str =str+";";
        }
        if (query.exec(str)){
            int i=0;
            int n = query.record().count();
            while (query.next()){
                QVector<QString> vc;
                for (int j=0;j<n;j++){
                    vc<<query.value(j).toString();//записываем всю информацию кроме порядкового номера
                }
                vec<<vc;
                i++;
            }
        }else{
            qDebug()<<"not select"<<db.lastError()<<str;
        }
        db.close();
    }else{
        qDebug()<<"not open"<<db.lastError();
    }
    return vec;
}

QVector<QString> SQLClass::selectColumn(QString tableName, QString columnName, QString whereStr){
    QVector<QString> vec;
    if (db.open()){
        QSqlQuery query;
        QString str = "SELECT "+tableName+"."+columnName+" FROM "+tableName;
        if (whereStr!=""){
            str=str+" WHERE "+whereStr+";";
        }else{
            str=str+";";
        }
        if (query.exec(str)){
            while (query.next()){
                vec<<query.value(0).toString();
            }
        }else{
            qDebug()<<"not select data"<<db.lastError();
        }
    }else{
        qDebug()<<"not open"<<db.lastError();
    }
    return vec;
}

QVector<QString> SQLClass::selectQueryColumn(QString qr){
    QVector<QString> vec;
    if (db.open()){
        QSqlQuery query;
        if (query.exec(qr)){
            while (query.next()){
                vec<<query.value(0).toString();
            }
        }else{
            qDebug()<<"not select data"<<db.lastError();
        }
    }else{
        qDebug()<<"not open"<<db.lastError();
    }
    return vec;
}

QStringList SQLClass::selectQueryColumnAsList(QString qr){
    QStringList vec;
    if (db.open()){
        QSqlQuery query;
        if (query.exec(qr)){
            while (query.next()){
                vec<<query.value(0).toString();
            }
        }else{
            qDebug()<<"not select data"<<db.lastError();
        }
    }else{
        qDebug()<<"not open"<<db.lastError();
    }
    return vec;
}

void SQLClass::deleteWhereData(QString tableName, QString whereStr){
//сразу готово
    if (db.open()){
 //подключились к базе данных
        QSqlQuery query;
        QString str = "DELETE FROM "+tableName+" WHERE "+whereStr+";";
        if (query.exec(str)){

        }else{
            qDebug()<<"not delete"<<db.lastError()<<str;
        }
        db.close();
    }else{
        qDebug()<<"not open"<<db.lastError();
    }
}

void SQLClass::dropDatabase(QString dbNm){
    if (db.open()){
        QSqlQuery query;
        QString str = "DROP DATABASE "+dbNm+";";
        if (query.exec(str)){
            qDebug()<<"drop Db"<<dbNm;
        }else{
            qDebug()<<"not drop Db"<<db.lastError()<<str;
        }
        db.close();
    }else{
        qDebug()<<"not open"<<db.lastError();
    }
}

bool SQLClass::isDatabase(){
    bool b = false;
    if (db.open()){
        b=true;
        db.close();
    }else{
        lastError = db.lastError().text();
    }
    return b;
}

SQLCursor* SQLClass::getCursor(QString tableName){
    QVector<QVector<QString> > vec = getQueryData("pragma table_info("+tableName+");");
    //имя поля, тип поля
    SQLCursor* cur = new SQLCursor;
    int n = vec.count();
    for (int i=0;i<n;i++){
        QString val = vec[i][2].toLower();
//        qDebug()<<vec[i][1];
        if (val.contains("varchar")){
            cur->putColumn(vec[i][1],SQLCursor::VARCHAR);
        }else if (val.contains("bool")){
            cur->putColumn(vec[i][1],SQLCursor::BOOL);
        }else if (val.contains("int")){
            cur->putColumn(vec[i][1],SQLCursor::INT);
        }else{
            cur->putColumn(vec[i][1],SQLCursor::VARCHAR);
        }
    }
    return cur;
}
