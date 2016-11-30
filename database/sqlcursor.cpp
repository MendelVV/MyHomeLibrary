#include "sqlcursor.h"

SQLCursor::SQLCursor(QObject *parent) : QObject(parent)
{

}

void SQLCursor::putColumn(QString name, int type){
    if (!columns.contains(name)){
        columns<<name;
        switch (type) {
        case VARCHAR:
            types<<"VARCHAR";
            break;
        case INT:
            types<<"INT";
            break;
        case BOOL:
            types<<"BOOL";
            break;
        default:
            break;
        }
    }
}

void SQLCursor::putLine(QVector<QString> line){
    if (columns.count()==line.count()){
        values<<line;
    }else{
        qDebug()<<"not put line"<<line;
    }
}

QString SQLCursor::getColumn(int n){
    if (n<columns.count()){
        return columns[n];
    }else{
        return "";
    }
}

QString SQLCursor::getColumnsToString(){
    QString res="(";
    int n = columns.count();
    for (int i=0;i<n;i++){
        if (i>0){
            res=res+",";
        }
        res=res+columns[i];
    }
    res=res+")";
    return res;
}

QString SQLCursor::getType(int n){
    if (n<types.count()){
        return types[n];
    }else{
        return "";
    }
}

QVector<QString> SQLCursor::getRow(int n){
    if (n<values.count()){
        return values[n];
    }else{
        QVector<QString> vec;
        return vec;
    }
}

QString SQLCursor::getRowToString(int n){
    if (n<values.count()){
        QString res="(";
        int m = columns.count();
        for (int i=0;i<m;i++){
            if (i>0){
                res=res+",";
            }
            res=res+valueToString(values[n][i],types[i]);
        }
        res=res+")";
        return res;
    }else{
        return "";
    }
}

QString SQLCursor::getRowForUpdate(int n){
    if (n<values.count()){
        QString res="";
        int m = columns.count();
        for (int i=0;i<m;i++){
            if (i>0){
                res=res+",";
            }
            res=res+columns[i]+"="+valueToString(values[n][i],types[i]);
        }
        return res;
    }else{
        return "";
    }
}

int SQLCursor::columnCount(){
    return columns.count();
}

int SQLCursor::rowCount(){
    return values.count();
}

QString SQLCursor::valueToString(QString value, QString type){
    QString res=value;
    res.replace("\"","'");
    if (type.contains("VARCHAR")){
        res="\""+res+"\"";
    }else if (type.contains("INT")){

    }
    return res;
}
