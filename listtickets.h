#ifndef LISTTICKETS_H
#define LISTTICKETS_H

#include <vector>
#include <QAction>
#include <QtSql>
#include <QDateTime>
#include <QMessageBox>
#include "ui_listtickets.h"
#include "editticket.h"
#include "item.h"

class Ticket
{
    int id;
    int i_id;
    QDateTime time;
    QString title;
    QString descr;
public:
    Ticket(int i = 0);
    bool read(int i);
    int Id() const { return id; }
    QDateTime Time() { return time; }
    QString Title() { return title; }
    QString Descr() { return descr; }
    void setPId(int i) { i_id = i; }
    void setTitle(QString str) { title = str; }
    void setDescr(QString str) { descr = str; }
    bool Insert();
    bool Remove();
};

class ListTicketsModel : public QAbstractTableModel
{
    Q_OBJECT

    int pid;
    QStringList header_data;
    std::vector<Ticket> list;
    void read_list(int id);

public:
    explicit ListTicketsModel(int id, QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    int key(int row) { return list.at(row).Id(); }

public slots:
    void updateList();
};

class ListTickets : public QDialog, private Ui::ListTickets
{
    Q_OBJECT

    int pid;
    ListTicketsModel *model;
    void addRecord();
    void delRecord();

private slots:
    void selectionChange();

public:
    explicit ListTickets(int id, QWidget *parent = 0);

signals:
    void updateList();
};

#endif // LISTTICKETS_H
