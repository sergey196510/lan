#include "listmovements.h"
#include "ui_listmovements.h"

ListMovementsModel::ListMovementsModel(int id, QObject *parent)
{

}

void ListMovementsModel::setDatePeriod(QDate f, QDate l)
{
    first = f;
    last = l;
}

void ListMovementsModel::reload_list(QDate f, QDate t)
{
    beginResetModel();
    setDatePeriod(f,t);
    readList();
    endResetModel();
}

void ListMovementsModel::readList()
{

}

ListMovements1Model::ListMovements1Model(int _id, QObject *parent)
{
    id = _id;

    attr.push_back("");
    attr.push_back("Пользователь");
    attr.push_back("Адрес");
    attr.push_back("МОЛ");
    attr.push_back("Счет");

    header_data << tr("Установлен") << tr("Демонтирован") << tr("Код") << tr("Наименование") << tr("Атрибут") << tr("Значение") << tr("Статус");
}

int ListMovements1Model::rowCount(const QModelIndex &parent) const
{
    return list.size();
}

int ListMovements1Model::columnCount(const QModelIndex &parent) const
{
    return header_data.size();
}

QVariant ListMovements1Model::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        if (index.column() == 0) {
            Movem m = list.at(index.row());
            return m.fd;
        }
        if (index.column() == 1) {
            Movem m = list.at(index.row());
            return m.ld;
        }
        if (index.column() == 2) {
            Movem m = list.at(index.row());
            return m.cod;
        }
        if (index.column() == 3) {
            Movem m = list.at(index.row());
            return m.item;
        }
        if (index.column() == 5) {
            Movem m = list.at(index.row());
            return m.attr;
        }
        if (index.column() == 4) {
            Movem m = list.at(index.row());
            return attr.at(m.type);
        }
        if (index.column() == 6) {
            Movem m = list.at(index.row());
            return ((m.active == 1) ? "Installed" : "Removed");
        }

        return QVariant();
    }

    if (role == Qt::TextColorRole) {
        Movem m = list.at(index.row());
        if (m.active == 0)
            return QVariant(QColor(Qt::gray));
        return QVariant();
    }

    return QVariant();
}

QVariant ListMovements1Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
         return QVariant();
     if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
         return header_data.at(section);
     }
//     else
//        return QString("%1").arg(section+1);
     return QVariant();

}

void ListMovements1Model::readList()
{
    QSqlQuery q;

    qDebug() << first << last.toString("yyyy-MM-dd");

    list.clear();

    QString query = QString("SELECT i_id, a_id, type, active, bd, ld FROM attr_link WHERE (bd >= '%1' AND bd <= '%2') OR (ld >= '%1' AND ld <= '%2') ORDER BY i_id, type, active, bd, ld")
            .arg(first.toString("yyyy-MM-dd"))
            .arg(last.toString("yyyy-MM-dd"));
    qDebug() << query;
//    q.prepare("SELECT i_id, a_id, type, active, bd, ld FROM attr_link WHERE (bd >= :f AND bd <= :l) OR (ld >= :f AND ld <= :l) ORDER BY i_id, type, bd, ld, active");
//    q.bindValue(":f", first.toString("yyyy-MM-dd"));
//    q.bindValue(":l", last.toString("yyyy-MM-dd"));
    if (!q.exec(query)) {
        qDebug() << q.lastError();
        return;
    }
    while (q.next()) {
//        qDebug() << q.value(0).toInt() << q.value(1).toInt() << q.value(2).toInt() << q.value(3).toInt() << q.value(4).toDate().toString("yyyy-MM-dd") << q.value(5).toDate();
        Movem m;
        Item i;
        Attribute a;
        i.read_by_id(q.value(0).toInt());
        a.Read(q.value(1).toInt());
        m.fd = q.value(4).toDate();
        m.ld = q.value(5).toDate();
        m.cod = i.Cod();
        m.item = i.Name();
        m.attr = a.Name();
        m.type = q.value(2).toInt();
        m.active = q.value(3).toInt();
        list.push_back(m);
    }
}

ListMovements2Model::ListMovements2Model(int _id, QObject *parent)
{
    id = _id;

    attr.push_back("");
    attr.push_back("Пользователь");
    attr.push_back("Адрес");
    attr.push_back("МОЛ");
    attr.push_back("Счет");

    moves = new itemMoves;
//    moves->readList(first, last);
}

int ListMovements2Model::rowCount(const QModelIndex &parent) const
{
    return moves->rowCount();
}

int ListMovements2Model::columnCount(const QModelIndex &parent) const
{
    return moves->columnCount();
}

QVariant ListMovements2Model::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole) {
        return moves->data(index.row(), index.column());
    }

    return QVariant();
}

QVariant ListMovements2Model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
        return moves->headerData(section);
    return QVariant();
}

void ListMovements2Model::readList()
{
    moves->readList(id, first, last);
}

ListMovements::ListMovements(ListMovementsModel *model, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListMovements)
{
    QDate dt;
    int mon, year;

    ui->setupUi(this);

    ui->fromDate->setCalendarPopup(true);
    dt.setDate(QDate::currentDate().year(), QDate::currentDate().month(), 1);
    ui->fromDate->setDate(dt);

    mon = dt.month();
    year = dt.year();
    mon += 1;
    if (mon > 12) {
        year += 1;
        mon = 1;
    }
    dt.setDate(year, mon, 1);
    ui->toDate->setCalendarPopup(true);
    ui->toDate->setDate(dt.addDays(-1));

    model->setDatePeriod(ui->fromDate->date(), ui->toDate->date());
    model->readList();
    ui->tableView->setModel(model);
    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(ui->reloadButton, SIGNAL(clicked()), SLOT(reload()));
    connect(this, SIGNAL(reload(QDate,QDate)), model, SLOT(reload_list(QDate,QDate)));
    connect(ui->saveButton, SIGNAL(clicked(bool)), SLOT(saveas()));
    connect(ui->okButton, SIGNAL(clicked()), SLOT(close()));
}

ListMovements::~ListMovements()
{
    delete ui;
}

void ListMovements::reload()
{
    if (ui->fromDate->date() > ui->toDate->date()) {
        QMessageBox::critical(this, tr("Date period"), tr("Date perios is inknown"));
        return;
    }

    emit reload(ui->fromDate->date(), ui->toDate->date());
}

void ListMovements::saveas()
{
    ListMovements1Model *model = static_cast<ListMovements1Model*>(ui->tableView->model());
    ExportData data(model, this);
    data.exportToCSV();
}
