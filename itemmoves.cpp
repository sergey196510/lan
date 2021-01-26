#include "itemmoves.h"

itemMoves::itemMoves(QObject *parent) : QObject(parent)
{
    header_data << tr("Код") << tr("Наименование") << tr("From") << tr("To") << tr("Date");
}

bool itemMoves::Insert(int item, int type, int prev, int next, QDate dt)
{
    QSqlQuery q;

    q.prepare("INSERT INTO item_moves(i_id, t_id, prev, next, dt) VALUES(:item, :type, :prev, :next, :dt)");
    q.bindValue(":item", item);
    q.bindValue(":type", type);
    q.bindValue(":prev", prev);
    q.bindValue(":next", next);
    q.bindValue(":dt", dt);
    return q.exec();
}

int itemMoves::rowCount()
{
    return list.size();
}

int itemMoves::columnCount()
{
    return header_data.size();
}

QVariant itemMoves::data(int row, int column)
{
    switch (column) {
    case 0:
        return list.at(row).cod;
        break;
    case 1:
        return list.at(row).name;
        break;
    case 2:
        return list.at(row).first;
        break;
    case 3:
        return list.at(row).next;
        break;
    case 4:
        return list.at(row).dt;
        break;
    default:
        break;
    }
    return QVariant();
}

QVariant itemMoves::headerData(int column)
{
    return header_data.at(column);
}

void itemMoves::readList(int id, QDate f, QDate l)
{
    QSqlQuery q;

    list.clear();

    if (id > 0) {
        q.prepare("SELECT i_id, prev, next, dt FROM item_moves WHERE i_id = :id AND dt >= :f AND dt <= :l AND t_id = 1 ORDER BY dt");
        q.bindValue(":id", id);
    }
    else
        q.prepare("SELECT i_id, prev, next, dt FROM item_moves WHERE dt >= :f AND dt <= :l AND t_id = 1 ORDER BY dt");
    q.bindValue(":f", f);
    q.bindValue(":l", l);
    if (!q.exec()) {
        qDebug() << q.lastError();
        return;
    }
    while (q.next()) {
        Item i;
        Attribute a;
        i.read_by_id(q.value(0).toInt());
        item.cod = i.Cod();
        item.name = i.Name();

        if (q.value(1).toInt() == 0)
            item.first = tr("Установлен");
        else {
            a.Read(q.value(1).toInt());
            item.first = a.Name();
        }

        if (q.value(2).toInt() == 0)
            item.next = tr("Демонтирован");
        else {
            a.Read(q.value(2).toInt());
            item.next = a.Name();
        }

        item.dt = q.value(3).toDate();
        list.append(item);
    }
}
