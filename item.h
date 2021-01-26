#ifndef ITEM_H
#define ITEM_H

#include <QObject>
#include <QtSql>
#include "grattr.h"
#include "lobject.h"
#include "link.h"
#include "itemmoves.h"

class Item
{
private:
    int id;
    QString cod;
    QString name;
    grAttr ga;
//    int addr_id;
//    int user_id;
//    int mol_id;
//    int schet_id;
    QDate dt;
    QString descr;

public:
    Item(int id = 0);
    bool read_by_id(int id);
    bool read_by_cod(QString cod);
    void setId(int i) { id = i; }
    void setCod(QString c) { cod = c; }
    void setName(QString n) { name = n; }
    void setAttr(grAttr);
//    void setAddr(int a) { addr_id = a; }
//    void setUser(int u) { user_id = u; }
//    void setMol(int m) { mol_id = m; }
//    void setSchet(int s) { schet_id = s; }
    void setDate(QDate d) { dt = d; }
    void setDescr(QString d) { descr = d; }
    int Id() { return id; }
    QString Cod() { return cod; }
    QString Name() { return name; }
    grAttr Attribute();
    //    int Addr() { return addr_id; }
//    int User() { return user_id; }
//    int Mol() { return mol_id; }
//    int Schet() { return schet_id; }
    QDate Date() { return dt; }
    QString Descr() { return descr; }
    int read_parent(int type);
    bool insert();
    bool update_cod();
    bool update_name();
};

#endif // ITEM_H
