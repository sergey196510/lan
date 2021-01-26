#ifndef ADDBOX_H
#define ADDBOX_H

#include "lcombobox.h"
#include <QtSql>

class AddrBox : public LComboBox
{
    Q_OBJECT

private:
    void read_list();

public:
    explicit AddrBox(QWidget *parent = 0);

signals:

public slots:

};

#endif // ADDBOX_H
