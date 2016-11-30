#ifndef CELLPLUSCLASS_H
#define CELLPLUSCLASS_H
#include <QString>
#include <QStringList>
#include <QDataStream>
#include <QObject>
#include <QTextEdit>
#include <QDate>
#include "cellclass.h"
#include <QApplication>

class D_FORM CellPlusClass: public CellClass
{
    Q_OBJECT
public:
    explicit CellPlusClass(QObject *parent = 0);
    explicit CellPlusClass(CellClass* cell, QObject *parent = 0);
    CellPlusClass(QString nameC, QString typeC, QString valueC, int rowC, int columnC, int widthC, int heightC=3, QObject *parent = 0);

    int getTextSize() const;
    void setTextSize(int value);

    QFont getFont() const;
    void setFont(QFont value);

    void setFontType(int);

    QString getAlignment() const;
    void setAlignment(QString value);

    QColor getColor() const;
    void setColor(const QColor &value);

    CellPlusClass* copy();

    friend QDataStream & operator << (QDataStream & out, const CellPlusClass &cell);
    friend QDataStream & operator >> (QDataStream & out, CellPlusClass &cell);
protected:
    //===========================================================================================================
//новые своства
    QFont font;//шрифт
    QString alignment;
    QColor color;

signals:

public slots:

};

#endif // CELLPLUSCLASS_H
