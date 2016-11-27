#ifndef SQLCURSOR_H
#define SQLCURSOR_H

#include <QObject>
#include <QVector>
#include <QDebug>
class SQLCursor : public QObject
{
    Q_OBJECT
public:
    enum {VARCHAR=0};
    enum {INT=1};
    enum {BOOL=2};
    explicit SQLCursor(QObject *parent = 0);
    void putColumn(QString name, int type);
    void putLine(QVector<QString> line);

    QString getColumn(int n);
    QString getColumnsToString();
    QString getType(int n);
    QVector<QString> getRow(int n);
    QString getRowToString(int n);
    QString getRowForUpdate(int n);
    int columnCount();
    int rowCount();

protected:
    QVector<QString> columns;
    QVector<QString> types;
    QVector<QVector<QString> > values;

    QString valueToString(QString value, QString type);
signals:

public slots:
};

#endif // SQLCURSOR_H
