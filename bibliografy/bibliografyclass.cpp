#include "bibliografyclass.h"

BibliografyClass::BibliografyClass(QString cd, QString tp, QString val, QString nt)
{
    code = cd;
    value = val;
    type = tp;
    note = nt;
}

void BibliografyClass::setValue(QString val){
    value=val;
}

void BibliografyClass::setType(QString tp){
    type = tp;
}

void BibliografyClass::setNote(QString nt){
    note = nt;
}

QString BibliografyClass::getCode(){
    return code;
}

QString BibliografyClass::getValue(){
    return value;
}

QString BibliografyClass::getType(){
    return type;
}

QString BibliografyClass::getNote(){
    return note;
}
