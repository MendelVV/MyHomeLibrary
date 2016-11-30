#ifndef FORMPLUSDATA_H
#define FORMPLUSDATA_H

#include <QList>
#include "formdata.h"
#include "cellplusclass.h"
#include <QFile>
#include <QDataStream>
#include <QMap>
#include <QtXml>

class D_FORM FormPlusData : public QObject
{
    Q_OBJECT
public:
    explicit FormPlusData(QString nm ="", QObject *parent = 0);
    explicit FormPlusData(FormData* form, QObject *parent = 0);
    void addCell(CellPlusClass*);
    void addCellToBlock(int,QString);
    CellPlusClass* getCell(int);
    CellPlusClass* getCell(QString);
    QString getValue(QString);//аналогично с getCell только сразу возвращает значение
    int getSize();
    QList<CellPlusClass*> getList();
    QMap<QString, CellPlusClass*> getMap();
    int getRow();
    int getColumn();

    void removeCell(CellPlusClass* cell);
    void removeCellWithBlock(int, QString);

    void setFormName(QString);
    void setMultyRowNum(int);
    void setCountMultyRow(int);

    QString getFormName();
    int getMultyRowNum();
    int getCountMultyRow();
    QVector<QString> getBlock(int);
    int getBlocksSize();

    bool contains(QString);

    friend QDataStream & operator << (QDataStream & out, const FormPlusData &form);
    friend QDataStream & operator >> (QDataStream & out, FormPlusData &form);

    void saveFormPlusData(QString str);
    void readFormPlusData(QString str);
    void saveFormPlusDataXML(QString str);//сохраняем форму в формате xml
protected:
    QString formName;//имя формы
    int multyRowNum;//=0;//номер множественной строки
    int countMultyRow;//=0;//количество строк в мультистроке

    int row;//=0;//количество строк
    int column;//=0;//количество столбцов
    QList<CellPlusClass*> listCells;//список ячеек
    QMap<QString, CellPlusClass*> mapCells;//словарь где названию соответствует ячейка

    QMap<int, QVector<QString> > blocks;//блоки ячеек для последоваательного вывода формы. одна ячейка может попадать в несколько блоков

signals:

public slots:
    void slotClearValues();//очищаем все значения кроме Label
    void slotRefreshWidgetsValues();//обновляем все значения в виджетах
};



#endif // FORMPLUSDATA_H
