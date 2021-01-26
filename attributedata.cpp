#include "attributedata.h"

AttributeData::AttributeData(int type)
{
    header_data << QObject::tr("Наименование") << QObject::tr("Статус");
    read_list(type);
}

void AttributeData::read_list(int type)
{
    QSqlQuery q;

    list.clear();

    q.prepare("SELECT id FROM attr_descr WHERE type = :type ORDER BY name");
    q.bindValue(":type", type);
    if (!q.exec()) {
        qDebug() << q.lastError();
        return;
    }
    while (q.next()) {
        Attribute a(q.value(0).toInt());
//        qDebug() << a.Flag() << a.Name();
        list.append(a);
    }
}

QVariant AttributeData::value(int row, int column)
{
    QString str;

    switch (column) {
//    case 0:
//        return list.at(row).Id();
//        break;
    case 0:
        return list.at(row).Name();
        break;
    case 1:
        if (list.at(row).Aist())
            str += "A";
        if (list.at(row).defaultUser())
            str += "U";
        if (list.at(row).Passive())
            str += "R";
        return str;
//        return list.at(row).Id();
        break;
    default:
        return QVariant();
        break;
    }
}
