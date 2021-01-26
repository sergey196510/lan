#ifndef LAN_H
#define LAN_H

#include <QMainWindow>
#include <QtSql>
#include "listitems.h"
#include "listmovements.h"
#include "listattribute.h"

namespace Ui {
class Lan;
}

class Lan : public QMainWindow
{
    Q_OBJECT

public:
    explicit Lan(QWidget *parent = 0);
    ~Lan();

private:
    Ui::Lan *ui;
    ListItems *items;
    bool dbopen();
    void readsettings();
    void writesettings();

private slots:
    void import_data();
    void movements();
    void movements2();
    void listAttributes();
};

#endif // LAN_H
