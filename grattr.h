#ifndef GRATTR_H
#define GRATTR_H

#include <QtSql>
#include "lobject.h"

class grAttr
{
private:
    int user;
    int address;
    int mol;
    int schet;
    int ReadByType(int id, int type);

public:
    grAttr();
    bool Read(int id);
    void setData(int u, int a, int m, int s);
    int User() { return user; }
    int Address() { return address; }
    int Mol() { return mol; }
    int Schet() { return schet; }
};

#endif // GRATTR_H
