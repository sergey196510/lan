#ifndef LISTATTRIBUTE_H
#define LISTATTRIBUTE_H

#include <QAbstractTableModel>
#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include "attributedata.h"
#include "lobject.h"
#include "editattribute.h"

namespace Ui {
class listAttribute;
}

class listAttributeModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit listAttributeModel(int type, QObject *parent = 0);
    ~listAttributeModel();
    QVariant data(const QModelIndex &index, int role) const;
    int columnCount(const QModelIndex &parent) const;
    int rowCount(const QModelIndex &parent) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    int key(int idx) { return ad->key(idx); }
    int size() { return ad->rowCount(); }

private:
//    QStringList header_data;
//    QList<Attribute> list;
    AttributeData *ad;
//    void read_list(int type);

public slots:
    void reload_data(int type);
};

class listAttribute : public QDialog
{
    Q_OBJECT

public:
    explicit listAttribute(QWidget *parent = 0);
    ~listAttribute();

private:
    Ui::listAttribute *ui;
    listAttributeModel *model;
    int get_selected_id();
    void finish_update(Attribute &);

private slots:
    void change_type();
    void change_line();
    void insert();
    void edit();
    void remove();
    void recovery();

signals:
    void changeAttribute(int);
};

#endif // LISTATTRIBUTE_H
