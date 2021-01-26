#include "addrbox.h"

AddrBox::AddrBox(QWidget *parent) :
    LComboBox(parent)
{
    qDebug() << objectName();

    read_list();
}

void AddrBox::read_list()
{
    QSqlQuery q;

    q.prepare("SELECT id,name FROM attr_descr WHERE type = 2 ORDER BY name");
    if (!q.exec()) {
        qDebug() << q.lastError();
        return;
    }

    while (q.next()) {
        addItem(q.value(1).toString(), q.value(0).toInt());
    }
}
