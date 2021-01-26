#ifndef SELATTR_H
#define SELATTR_H

#include <QDialog>
#include <QFileDialog>
#include <QDate>
#include <QMessageBox>
#include "item.h"
#include "attribute.h"
#include "lobject.h"

namespace Ui {
class SelAttr;
}

class SelAttr : public QDialog
{
    Q_OBJECT

public:
    explicit SelAttr(QWidget *parent = 0);
    ~SelAttr();
//    void read_data(int type);
//    void setValue(int);
    void setData(grAttr);
//    void setType(int);
    QVariant Mol();
    QDate Date();
    QString Description();
    QString fileName();
    QVariant User();
    QVariant Address();
    grAttr Attr();

private:
    Ui::SelAttr *ui;
    int type;

private slots:
    void selectFile();
    void pressOk();
//    void change_mol();

signals:
    void updateAttribute();
};

#endif // SELATTR_H
