#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <QObject>
#include <QtSql>

class Attribute
{
private:
    int id;
    int type;
    int flag;
    QString name;

public:
    Attribute(int id = 0);
    bool Read(int id);
    int Insert();
    bool Update();
//    bool Remove();
    bool Recovery();
    int Id() const { return id; }
    QString Name() const { return name; }
    int Type() { return type; }
    int Flag() { return flag; }
    int Aist() const { return flag&0x1; }
    int Passive() const { return flag&0x2; }
    int defaultUser() const { return flag&0x4; }
    void setId(int i) { id = i; }
    void setType(int t) { type = t; }
    void setFlag(int f) { flag = f; }
    void setName(QString n) { name = n; }
    int getDefaultUser(int type);
    bool setDefaultUser();
    bool checkItem();
    bool setAist();
    bool setPassive();
    bool setActive();
};

#endif // ATTRIBUTE_H
