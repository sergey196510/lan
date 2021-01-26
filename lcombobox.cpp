#include "lcombobox.h"

LComboBox::LComboBox(QWidget *parent) :
    QComboBox(parent)
{
}

void LComboBox::setValue(QVariant val)
{
    int i = findData(val);
    if (i != -1)
        setCurrentIndex(i);
    else
        setCurrentIndex(0);
}

QVariant LComboBox::Value()
{
    return itemData(currentIndex());
}

void LComboBox::read_data(int t)
{
    QSqlQuery q;

    this->clear();

    type = t;
    addItem("");

    q.prepare("SELECT id,name,flag FROM attr_descr WHERE type = :type ORDER BY name");
    q.bindValue(":type", type);
    if (!q.exec()) {
        qDebug() << q.lastError();
        return;
    }

    while (q.next()) {
        if (q.value(2).toInt() & 2)
            continue;
        addItem(q.value(1).toString(), q.value(0).toInt());
    }

    this->setValue(0);
}

void LComboBox::reload_data()
{
    this->clear();
    read_data(type);
    emit Updated();
}
