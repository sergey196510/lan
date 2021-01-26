#ifndef LISTITEMS_H
#define LISTITEMS_H

#include <QClipboard>
#include <QWidget>
#include <QAbstractTableModel>
#include <QtSql>
#include <QMessageBox>
#include <QTextEdit>
#include <QInputDialog>
#include <QSortFilterProxyModel>
#include "edititem.h"
#include "item.h"
#include "address.h"
#include "attribute.h"
#include "selattr.h"
#include "showhistory.h"
#include "search.h"
#include "lobject.h"
#include "editname.h"
#include "exportdata.h"
#include "listtickets.h"
#include "listmovements.h"

struct attrSearch {
//    QString cod;
    int mol;
    int addr;
    int user;
public:
    attrSearch() {
//        cod.clear();
        mol = 0;
        addr = 0;
        user = 0;
    }
};

namespace Ui {
class ListItems;
}

class ListItemsModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit ListItemsModel(QObject *parent = 0);
    ~ListItemsModel();
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    int key(int row);
//    int Rows() { return rowCount(QModelIndex()); }
//    int Columns() { return columnCount(QModelIndex()); }

public slots:
    void reload_list(attrSearch);
    QList<Item> List() { return list; }
    void sort(int col, Qt::SortOrder);

private:
    QStringList header_data;
    QList<Item> list;
    QList<Item> read_list(attrSearch);
    QVariant item(int row, int col);
    int sortcolumn;
    Qt::SortOrder sortorder;
    bool compare(QVariant, QVariant, Qt::SortOrder);
};

class ListItems : public QWidget
{
    Q_OBJECT

public:
    explicit ListItems(QWidget *parent = 0);
    ~ListItems();
    QList<QAction*> acts;
    QList<int> get_selected_id();

public slots:
    void select_attr(int idx);
    void update_attr(int type);
//    void check_cod(QString c);
    void new_record();
    void update_record();
    void delete_record();
    void history();
    void history2();
    void hist_user();
    void export_data();

private:
    Ui::ListItems *ui;
    ListItemsModel *model;
    QList<QPoint> point;
    Search *s;
    int position;
    QModelIndexList indexes;
    QModelIndexList::iterator idx;
//    int x,y;
//    int status;

private slots:
    void change_attribute();
    void update_attribute();
    void update_cod();
    void update_name();
    void search_text();
    void search_first(int,QString);
    void search_prev();
    void search_next();
    void search_last();
    void copy_text();
    void selectAll();
    void tickets();

signals:
    void reload_list(attrSearch);
    void SearchFirst(int,int);
};

#endif // LISTITEMS_H
