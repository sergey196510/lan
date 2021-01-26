#include "link.h"

Link::Link()
{
    id = 0;
    i_id = 0;
    a_id = 0;
    type = 0;
    active = 0;
    d_id = 0;
    descr.clear();
}

void Link::setData(int iid, QDate d1, int a, QString d, int f, QDateTime t)
{
    i_id = iid;
//    a_id = aid;
//    type = t;
    dt = d1;
    active = a;
    descr = d;
    file = f;
    tm = t;
}

bool Link::findActive(int iid, int type)
{
    QSqlQuery q;

    q.prepare("SELECT id,i_id,a_id,d_id FROM attr_link WHERE i_id = :iid AND type = :type AND active = 1");
    q.bindValue(":iid", iid);
    q.bindValue(":type", type);
    if (!q.exec()) {
        qDebug() << q.lastError();
        return false;
    }
    if (q.size() > 1) {
        qDebug() << "Many active attribute" << iid << type;
    }
    if (q.next()) {
        id = q.value(0).toInt();
        i_id = q.value(1).toInt();
        a_id = q.value(2).toInt();
        d_id = q.value(3).toInt();
//        qDebug() << i_id << a_id << type;
        return true;
    }
    return false;
}

bool Link::Insert(int aid, int tp)
{
    QSqlQuery q;

    a_id = aid;
    type = tp;

    if (i_id == 0 || a_id == 0 || type == 0 || active == 0)
        return false;

//    int did = insert_document();

    q.prepare("INSERT INTO attr_link(i_id, a_id, type, bd, active, descr, d_id, open) VALUES(:iid, :aid, :type, :bdate, :active, :descr, :did, :tm)");
    q.bindValue(":iid", i_id);
    q.bindValue(":aid", a_id);
    q.bindValue(":type", type);
    q.bindValue(":bdate", dt);
    q.bindValue(":active", active);
    q.bindValue(":descr", descr);
    q.bindValue(":did", d_id);
    q.bindValue(":tm", tm);
    if (!q.exec()) {
        qDebug() << q.lastError();
        return false;
    }
    return true;
}

bool Link::Update(int ol, int nl, int type)
{
    if (nl != ol) {
        if (ol) {
            if (setPassive(i_id, type) == false) {
//                q.exec("ROLLBACK");
                return false;
            }
        }
        if (nl) {
            if (Insert(nl, type) == false) {
//                q.exec("ROLLBACK");
                return false;
            }
        }
        itemMoves im;
        if (!im.Insert(i_id, type, ol, nl, dt)) {
            return false;
        }
    }

    return true;
}

int Link::insert_document(QString file)
{
    QFile f;
    QByteArray arr;
    QSqlQuery q;

    if (file.size() == 0)
        return 0;

    f.setFileName(file);
    if (!f.open(QFile::ReadOnly))
        return 0;
    arr = f.readAll();
    f.close();

    q.prepare("INSERT INTO document(data) VALUES(:data)");
    q.bindValue(":data", arr);
    if (!q.exec()) {
        qDebug() << q.lastError();
        return 0;
    }
    q.prepare("SELECT MAX(id) FROM document");
    if (!q.exec()) {
        qDebug() << q.lastError();
        return 0;
    }
    if (!q.next()) {
        return 0;
    }
    return q.value(0).toInt();
}

bool Link::setPassive(int i, int t)
{
    QSqlQuery q;

    id = i;

    if (id == 0)
        return false;

    q.prepare("UPDATE attr_link SET active = 0, ld = :dt, close = :tm WHERE i_id = :id AND type = :type AND active = 1");
    q.bindValue(":dt", dt);
    q.bindValue(":tm", tm);
    q.bindValue(":id", id);
    q.bindValue(":type", t);
    if (!q.exec()) {
        qDebug() << q.lastError();
        return false;
    }
    return true;
}
