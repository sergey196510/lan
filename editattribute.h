#ifndef EDITATTRIBUTE_H
#define EDITATTRIBUTE_H

#include <QDialog>
#include "attribute.h"

namespace Ui {
class EditAttribute;
}

class EditAttribute : public QDialog
{
    Q_OBJECT

public:
    explicit EditAttribute(QString str, int t, QWidget *parent = 0);
    ~EditAttribute();
    void setValue(Attribute attr);
    Attribute Value();

private:
    Ui::EditAttribute *ui;
    QList<QString> types;
    int type;
};

#endif // EDITATTRIBUTE_H
