#ifndef WGRATTR_H
#define WGRATTR_H

#include <QWidget>
#include "grattr.h"
#include "lobject.h"

namespace Ui {
class WGrAttr;
}

class WGrAttr : public QWidget
{
    Q_OBJECT

public:
    explicit WGrAttr(QWidget *parent = 0);
    ~WGrAttr();
    void setData(grAttr);
    grAttr Data();

private:
    Ui::WGrAttr *ui;

private slots:
    void changeUser();
    void changeMol();

signals:
    void updatedAttribute();
};

#endif // WGRATTR_H
