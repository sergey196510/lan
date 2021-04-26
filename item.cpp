#include "item.h"

Item::Item(int _id):
    id(_id)
{
//    id = _id;
    cod.clear();
    name.clear();
//    addr_id = 0;
//    user_id = 0;
//    mol_id = 0;
//    schet_id = 0;

    read_by_id(id);
}

bool Item::read_by_id(int _id)
{
    QSqlQuery q;

    if (_id == 0)
        return false;

    id = _id;

    q.prepare("SELECT cod,name FROM item WHERE id = :id");
    q.bindValue(":id", id);
    if (!q.exec()) {
        qDebug() << q.lastError();
        return false;
    }
    if (!q.next())
        return false;

    cod = q.value(0).toString();
    name = q.value(1).toString();
    ga.Read(id);

    return true;
}

bool Item::read_by_cod(QString _cod)
{
    QSqlQuery q;

    cod = _cod;

    q.prepare("SELECT id FROM item WHERE cod = :cod");
    q.bindValue(":cod", cod);
    if (!q.exec()) {
        qDebug() << q.lastError();
        return false;
    }
    if (q.next())
        return read_by_id(q.value(0).toInt());
    return false;
}

int Item::read_parent(int type)
{
    QSqlQuery q;

    q.prepare("SELECT a_id FROM attr_link WHERE i_id = :id AND active = 1 AND type = :type");
    q.bindValue(":id", id);
    q.bindValue(":type", type);
    if (!q.exec()) {
        qDebug() << q.lastError();
        return 0;
    }
    if (q.next())
        return q.value(0).toInt();
    return 0;
}

bool Item::insert()
{
    QSqlQuery q;
    Link l;
    itemMoves i;

    q.exec("BEGIN");

    q.prepare("INSERT INTO item(cod,name) VALUES(:cod, :name)");
    q.bindValue(":cod", cod);
    q.bindValue(":name", name);
    if (!q.exec()) {
        qDebug() << q.lastError();
        return false;
    }
    q.prepare("SELECT MAX(id) FROM item");
    if (!q.exec()) {
        qDebug() << q.lastError();
        q.exec("ROLLBACK");
        return false;
    }
    if (!q.next()) {
        q.exec("ROLLBACK");
        return false;
    }
    id = q.value(0).toInt();

    QDateTime tm = QDateTime().currentDateTime();
    l.setData(id, dt, 1, QString(), 0, tm);
    if (Attribute().User()) {
//        l.setData(id, dt, 1, QString(), QString());
        if (l.Insert(Attribute().User(), LObject::User) == false) {
            q.exec("ROLLBACK");
            return false;
        }
        if (i.Insert(id, LObject::User, 0, Attribute().User(), dt) == false) {
            q.exec("ROLLBACK");
            return false;
        }
    }
    if (Attribute().Address()) {
//        l.setData(id, dt, 1, QString(), QString());
        if (l.Insert(Attribute().Address(), LObject::Address) == false) {
            q.exec("ROLLBACK");
            return false;
        }
        if (i.Insert(id, LObject::Address, 0, Attribute().Address(), dt) == false) {
            q.exec("ROLLBACK");
            return false;
        }
    }
    if (l.Insert(Attribute().Mol(), LObject::Mol) == false) {
        q.exec("ROLLBACK");
        return false;
    }
    if (i.Insert(id, LObject::Mol, 0, Attribute().Mol(), dt) == false) {
        q.exec("ROLLBACK");
        return false;
    }
//    l.setData(id, dt, 1, QString(), QString());
    if (l.Insert(Attribute().Schet(), LObject::Schet) == false) {
        q.exec("ROLLBACK");
        return false;
    }
    if (i.Insert(id, LObject::Schet, 0, Attribute().Schet(), dt) == false) {
        q.exec("ROLLBACK");
        return false;
    }

    q.exec("COMMIT");
    return true;
}

bool Item::update_cod()
{
    QSqlQuery q;

    q.prepare("UPDATE item SET cod = :cod WHERE id = :id");
    q.bindValue(":id", id);
    q.bindValue(":cod", cod);
    if (!q.exec()) {
        qDebug() << q.lastError();
        return false;
    }
    return true;
}

bool Item::update_name()
{
    QSqlQuery q;

    q.prepare("UPDATE item SET name = :name WHERE id = :id");
    q.bindValue(":id", id);
    q.bindValue(":name", name);
    if (!q.exec()) {
        qDebug() << q.lastError();
        return false;
    }
    return true;
}

grAttr Item::Attribute()
{
    return ga;
}

void Item::setAttr(grAttr a)
{
    ga = a;
}
