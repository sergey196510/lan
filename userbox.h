#ifndef USERBOX_H
#define USERBOX_H

#include "lcombobox.h"
#include <QtSql>

class UserBox : public LComboBox
{
    Q_OBJECT

private:
    void read_list();

public:
    explicit UserBox(QWidget *parent = 0);

signals:

public slots:

};

#endif // USERBOX_H
