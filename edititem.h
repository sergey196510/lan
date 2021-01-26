#ifndef EDITITEM_H
#define EDITITEM_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include "item.h"
#include "editattribute.h"
#include "grattr.h"
#include "lobject.h"

namespace Ui {
class EditItem;
}

class EditItem : public QDialog
{
    Q_OBJECT

public:
    explicit EditItem(QWidget *parent = 0);
    ~EditItem();
    Item data();
    void setUser(int);

private:
    Ui::EditItem *ui;
    int type;
    int id;

private slots:
    void check_cod();
//    void check_mol();
    void pressOk();

signals:
    void updateAttribute();
};

#endif // EDITITEM_H
