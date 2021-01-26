#ifndef ADDRESS_H
#define ADDRESS_H

#include <QObject>
#include <QtSql>

class Address
{
private:
    int id;
    QString name;
    bool read_by_id();

public:
    Address(int id = 0);
    int Id() { return id; }
    QString Name() { return name; }
};

#endif // ADDRESS_H
