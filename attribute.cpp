#include "attribute.h"

Attribute::Attribute(int _id)
{
    id = 0;
    type = 0;
    flag = 0;

    if (_id == 0)
        return;

    id = _id;
    Read(id);
}

bool Attribute::Read(int _id)
{
    QSqlQuery q;

    id = _id;

    q.prepare("SELECT type, name, flag FROM attr_descr WHERE id = :id");
    q.bindValue(":id", id);
    if (!q.exec()) {
        qDebug() << q.lastError();
        return false;
    }
    if (!q.next())
        return false;

    type = q.value(0).toInt();
    name = q.value(1).toString();
    flag = q.value(2).toInt();

    return true;
}

int Attribute::Insert()
{
    QSqlQuery q;

    q.prepare("INSERT INTO attr_descr(name, type, active, flag) VALUES(:name, :type, 1, :flag)");
    q.bindValue(":type", type);
    q.bindValue(":name", name);
    q.bindValue(":flag", flag);
    if (!q.exec()) {
        qDebug() << q.lastError();
        return 0;
    }
    q.prepare("SELECT MAX(id) FROM attr_descr");
    if (!q.exec()) {
        qDebug() << q.lastError();
        return 0;
    }
    if (!q.next()) {
        return 0;
    }
    return q.value(0).toInt();
}

bool Attribute::Update()
{
    QSqlQuery q;

    q.prepare("UPDATE attr_descr SET name = :name, flag = :flag WHERE id = :id");
    q.bindValue(":name", name);
    q.bindValue(":id", id);
    q.bindValue(":flag", flag);
    if (!q.exec()) {
        qDebug() << q.lastError();
        return false;
    }

    return true;
}

//bool Attribute::Remove()
//{
//    return true;
//}

bool Attribute::Recovery()
{
    return true;
}

bool Attribute::checkItem()
{
    QSqlQuery q;

    q.prepare("SELECT i_id FROM attr_link WHERE a_id = :id AND active = 1");
    q.bindValue(":id", id);
    if (!q.exec()) {
        qDebug() << q.lastError();
        return true;
    }
    if (q.next())
        return true;
    return false;
}

bool Attribute::setAist()
{
    flag |= 0x01;
}

bool Attribute::setPassive()
{
//    QSqlQuery q;

//    if (id == 0)
//        return false;

    flag |= 0x02;
    Update();

//    q.prepare("UPDATE attr_descr SET flag = :flag WHERE id = :id");
//    q.bindValue(":flag", flag);
//    q.bindValue(":id", id);
//    if (!q.exec()) {
//        qDebug() << q.lastError();
//        return false;
//    }
    return true;
}

bool Attribute::setActive()
{
//    QSqlQuery q;

    qDebug() << flag;
    flag &= (~0x02);
    qDebug() << flag;
    Update();

//    q.prepare("UPDATE attr_descr SET flag = :flag WHERE id = :id");
//    q.bindValue(":flag", flag);
//    q.bindValue(":id", id);
//    if (!q.exec()) {
//        qDebug() << q.lastError();
//        return false;
//    }
    return true;
}

bool Attribute::setDefaultUser()
{
    QSqlQuery q;
    QMap<int,int> list;

    flag |= 0x04;
//    flag &= (~0x04);

//    q.prepare("SELECT id,fla FROM attr_descr WHERE type = :type");
//    q.bindValue(":type", type);
//    if (!q.exec()) {
//        qDebug() << q.lastError();
//        return false;
//    }
//    while (q.next()) {
//        if (!list.contains(q.value(0).toInt()))
//            list[q.value(0).toInt()] = q.value(1).toInt();
//    }

    return true;
}

int Attribute::getDefaultUser(int tp)
{
    QSqlQuery q;

    q.prepare("SELECT id,flag FROM attr_descr WHERE type = :type");
    q.bindValue(":type", tp);
    if (!q.exec()) {
        qDebug() << q.lastError();
        return 0;
    }
    while (q.next()) {
        flag = q.value(1).toInt();
        if (defaultUser()) {
            id = q.value(0).toInt();
            return id;
        }
    }

    return false;
}
