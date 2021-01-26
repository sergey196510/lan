#include "userbox.h"

UserBox::UserBox(QWidget *parent) :
    LComboBox(parent)
{
    qDebug() << objectName();

    read_list();
}

void UserBox::read_list()
{
    QSqlQuery q;

    addItem("All", 0);

    q.prepare("SELECT id,name FROM attr_descr WHERE type = 1 ORDER BY name");
    if (!q.exec()) {
        qDebug() << q.lastError();
        return;
    }

    while (q.next()) {
        addItem(q.value(1).toString(), q.value(0).toInt());
    }
}
