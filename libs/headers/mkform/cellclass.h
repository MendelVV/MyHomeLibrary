#ifndef CELLCLASS_H
#define CELLCLASS_H
#include <QString>
#include <QStringList>
#include <QDataStream>
#include <QObject>
#include <QTextEdit>
#include <QDate>
#include "ddll.h"

class D_FORM CellClass: public QObject
{
    Q_OBJECT
public:
    explicit CellClass(QObject *parent = 0);
    CellClass(QString nameC, QString typeC, QString valueC, int rowC, int columnC, int widthC, int heightC=3, QObject *parent = 0);
    void setWidth(int);
    void setHeight(int);
    void setTypeCell(QString);
    void setColumn(int);
    void setRow(int);
    void setMergeColumn(int);
    void setMergeRow(int);
    void setMultyRowNum(int);
    void setList(QStringList);
    void setValue(QString);
    void setFormula(QString);
    void setNameCell(QString);

    int getWidth();
    int getHeight();
    QString getTypeCell();
    int getColumn();
    int getRow();
    int getMergeColumn();
    int getMergeRow();
    int getMultyRowNum();
    QStringList getList();
    QString getValue();
    QString getFormula();
    QString getNameCell();
    CellClass* copy();

    bool isEnable;//=true;

    friend QDataStream & operator << (QDataStream & out, const CellClass &cell);
    friend QDataStream & operator >> (QDataStream & out, CellClass &cell);
protected:
    int width;//=0;//ширина ячейки
    int height;//=20;//ширина ячейки
    QString typeCell;//="No";//возможные значения "Number", "NumberInt", "Label", "MultyLabel", "Text", "MultyText","Combobox", "Checkbox", "Formula","Password" "No"
    int column;//=0;//номер колонки
    int row;//=0;//номер строки
    int mergeColumn;//=1;//скольно занимает мест в строке
    int mergeRow;//=1;//скольно занимает мест в строке
    int multyRowNum;//=0;//позиция в мультистроке. если 0 то не мультистрока, если больше то указывает на позицию в наборе мультистрок
    QStringList list;//список возможных значений, только для Combobox
    QString value;//="";//значение, если не пусто
    QString formula;//содержание формулы, если задана формула
    QString nameCell;//имя ячейки (вместо адреса из excel)
signals:
    void changed(QString);
    void changeValueWidget();
    void signalDoubleClick();
    void signalPress();
    void signalShiftEnter();
    void signalEditList();

    void signalResizeHeight(int);
    void signalResizeWidth(int);
public slots:
    void slotChangeValue(QString s);
    void slotChangeValue(QDate date);
    void slotChangeValue(bool b);
    void slotChangeMultyValue();
};


#endif // CELLCLASS_H
