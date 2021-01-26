#include "grattr.h"

grAttr::grAttr()
{
}

void grAttr::setData(int u, int a, int m, int s)
{
    user = u;
    address = a;
    mol = m;
    if (mol == 0) {
        mol = 90;
    }
    schet = s;
}

int grAttr::ReadByType(int id, int type)
{
    QSqlQuery q;

    q.prepare("SELECT a_id FROM attr_link WHERE i_id = :id AND active = 1 AND type = :type");
    q.bindValue(":id", id);
    q.bindValue(":type", type);
    if (!q.exec()) {
        qDebug() << q.lastError();
        return 0;
    }
    if (q.numRowsAffected() > 1) {
        qDebug() << "Item:" << id << "Atribute:" << q.value(0).toInt() << "Number:" << q.numRowsAffected();
        return 0;
    }
    if (q.next())
        return q.value(0).toInt();
    return 0;
}

bool grAttr::Read(int id)
{
    user = ReadByType(id, LObject::User);
    address = ReadByType(id, LObject::Address);
    mol = ReadByType(id, LObject::Mol);
    schet = ReadByType(id, LObject::Schet);

    return true;
}
