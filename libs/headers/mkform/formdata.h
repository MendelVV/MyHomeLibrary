#ifndef FORMDATA_H
#define FORMDATA_H
#include <QList>
#include "cellclass.h"
#include <QFile>
#include <QDataStream>
#include <QMap>
#include <QtXml>

class D_FORM FormData: public QObject
{
    Q_OBJECT
public:
    FormData(QObject* parent=0);
    static int ct;
    void addCell(CellClass*);
    void insertCell(int, CellClass*);
    CellClass* getCell(int);
    CellClass* getCell(QString);
    CellClass* getCell(QString, int);
    QString getValue(QString);//аналогично с getCell только сразу возвращает значение
    int getSize();
    QList<CellClass*> getList();
    QList<CellClass*> getRowMarks();
    QList<CellClass*> getColumnMarks();
    QMap<QString, CellClass*> getMap();
    int getRow();
    int getColumn();
    void addRowMark(CellClass*);
    void addColumnMark(CellClass*);

    void removeCell(CellClass* cell);

    void setSchoolCode(QString);
    void setClassCode(QString);
    void setFormName(QString);
    void setSheetName(QString);
    void setSheetNum(int);
    void setMultyRowNum(int);
    void setCountMultyRow(int);
    void setRowMarks(QList<CellClass*> listMarks);

    QString getSchoolCode();
    QString getClassCode();
    QString getFormName();
    QString getSheetName();
    int getSheetNum();
    int getMultyRowNum();
    int getCountMultyRow();

    bool contains(QString);

    bool isCreated;//=false;//указывает создаем или открываем форму
    bool isFinalForm;//=false;//указывает нужно ли вставлять мультистроки. обязательно сохранять этот параметр

    friend QDataStream & operator << (QDataStream & out, const FormData &form);
    friend QDataStream & operator >> (QDataStream & out, FormData &form);

    void saveFormData(QString str);
    void readFormData(QString str);
    void saveFormDataXML(QString str);//сохраняем форму в формате xml

protected:
    QString schoolCode;//код школы
    QString classCode;//код класса
    QString formName;//имя формы
    QString sheetName;//имя листа
    int sheetNum;//=0;//номер листа
    int multyRowNum;//=0;//номер множественной строки
    int countMultyRow;//=0;//количество строк в мультистроке

    int row;//=0;//количество строк
    int column;//=0;//количество столбцов
    QList<CellClass*> listCells;//список ячеек
    QList<CellClass*> rowMarks;//верхняя линейка
    QList<CellClass*> columnMarks;//левая линейка
    QMap<QString, CellClass*> mapCells;//словарь где строке координат row%column% соответствует тип ячейки
signals:
public slots:
    void slotClearValues();//очищаем все значения кроме Label
    void slotRefreshWidgetsValues();//обновляем все значения в виджетах

};

#endif // FORMDATA_H
