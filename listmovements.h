#ifndef LISTMOVEMENTS_H
#define LISTMOVEMENTS_H

#include <QDialog>
#include <QMessageBox>
#include <QAbstractTableModel>
#include <QtSql>
#include "item.h"
#include "attribute.h"
#include "exportdata.h"
#include "itemmoves.h"

struct Movem {
    QString cod;
    QString item;
    QString attr;
    QDate fd;
    QDate ld;
    int type;
    int active;
    Movem() {
        cod.clear();
        item.clear();
        attr.clear();
        type = 0;
        active = 0;
    }
};

namespace Ui {
class ListMovements;
}

class ListMovementsModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ListMovementsModel(int id = 0, QObject *parent = 0);
    QDate first, last;
    int id;
    void setDatePeriod(QDate, QDate);
    virtual void readList();

public slots:
    void reload_list(QDate, QDate);
};

class ListMovements1Model : public ListMovementsModel
{
    Q_OBJECT

private:
    QList<QString> attr;
    QList<Movem> list;
    QStringList header_data;

public:
    explicit ListMovements1Model(int id = 0, QObject *parent = 0);
    void readList();
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

//public slots:
//    void reload_list(QDate, QDate);
};

class ListMovements2Model : public ListMovementsModel
{
    Q_OBJECT

private:
    QList<QString> attr;
    itemMoves *moves;

public:
    explicit ListMovements2Model(int id = 0, QObject *parent = 0);
//    void setDatePeriod(QDate, QDate);
    void readList();
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
};

class ListMovements : public QDialog
{
    Q_OBJECT

public:
    explicit ListMovements(ListMovementsModel *model, QWidget *parent = 0);
    ~ListMovements();

private:
    Ui::ListMovements *ui;
//    ListMovementsModel *model;

private slots:
    void reload();
    void saveas();

signals:
    void reload(QDate, QDate);
};

#endif // LISTMOVEMENTS_H
