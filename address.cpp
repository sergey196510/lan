#include "address.h"

Address::Address(int _id):
    id(_id)
{
//    id = 0;
    name.clear();

    if (_id == 0)
        return;

//    id = _id;
    read_by_id();
}

bool Address::read_by_id()
{
    QSqlQuery q;

    q.prepare("SELECT name FROM address WHERE id = :id");
    q.bindValue(":id", id);
    if (!q.exec()) {
        qDebug() << q.lastError();
        return false;
    }
    if (q.next()) {
        name = q.value(0).toString();
        return true;
    }
    return false;
}
