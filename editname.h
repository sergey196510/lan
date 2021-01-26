#ifndef EDITNAME_H
#define EDITNAME_H

#include <QDialog>

namespace Ui {
class EditName;
}

class EditName : public QDialog
{
    Q_OBJECT

public:
    explicit EditName(QString str, QWidget *parent = 0);
    ~EditName();
    void setValue(QString str);
    QString Value();

private:
    Ui::EditName *ui;
};

#endif // EDITNAME_H
