#ifndef ATTRIBUTEDATA_H
#define ATTRIBUTEDATA_H

#include <QObject>
#include <QtSql>
#include "attribute.h"


class AttributeData
{
public:
    AttributeData(int type);
    void read_list(int type);
    int key(int idx) { return list.at(idx).Id(); }
    int columnCount() { return header_data.size(); }
    int rowCount() { return list.size(); }
    QVariant value(int row, int col);
    QVariant hedaerValue(int col) { return header_data.at(col); }
    int isPassive(int idx) const { return list.at(idx).Passive(); }

private:
    QVector<Attribute> list;
    QStringList header_data;
};

#endif // ATTRIBUTEDATA_H
