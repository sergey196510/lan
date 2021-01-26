#ifndef LINK_H
#define LINK_H

#include <QObject>
#include <QtSql>
#include <QDate>
#include "itemmoves.h"

class Link
{
private:
    int id;
    int i_id;
    int a_id;
    int type;
    int active;
    QDate dt;
//    QDate ld;
    QString descr;
    int file;
    int d_id;
    QDateTime tm;

public:
    Link();
    void setData(int iid, QDate d, int a, QString s, int f, QDateTime t);
    bool findActive(int iid, int type);
    bool Insert(int, int);
    bool Update(int, int, int);
    bool setPassive(int, int);
    int Attr() { return a_id; }
    int Doc() { return d_id; }
    int insert_document(QString file);
};

#endif // LINK_H
