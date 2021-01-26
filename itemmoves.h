#ifndef ITEMMOVES_H
#define ITEMMOVES_H

#include <QObject>
#include <QStringList>
#include <QtSql>
#include "item.h"
#include "attribute.h"

class itemMoves : public QObject
{
    Q_OBJECT

private:
    struct Data {
        QString cod;
        QString name;
        QString first;
        QString next;
        QDate dt;
    } item;

    QList<Data> list;
    QStringList header_data;

public:
    explicit itemMoves(QObject *parent = 0);
    int rowCount();
    int columnCount();
    QVariant data(int row, int column);
    QVariant headerData(int column);
    void readList(int id, QDate, QDate);
    bool Insert(int, int, int, int, QDate);

signals:

public slots:
};

#endif // ITEMMOVES_H
