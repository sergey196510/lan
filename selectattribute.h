#ifndef SELECTATTRIBUTE_H
#define SELECTATTRIBUTE_H

#include <QWidget>
#include <QMessageBox>
#include "editattribute.h"
#include "attribute.h"

namespace Ui {
class SelectAttribute;
}

class SelectAttribute : public QWidget
{
    Q_OBJECT

public:
    explicit SelectAttribute(QWidget *parent = 0);
    ~SelectAttribute();
    void read_data(int type);
    void setValue(int val);
    QVariant Value();

private:
    Ui::SelectAttribute *ui;
    int id;
    int type;

private slots:
    void insert_value();
//    void delete_value();
    void attrUpdated();

signals:
    void change_data();
    void changedAttribute();
    void Updated(int);
};

#endif // SELECTATTRIBUTE_H
