#include "listtickets.h"

Ticket::Ticket(int i)
{
    id = 0;
    i_id = 0;
    time = QDateTime().currentDateTime();
    title.clear();
    descr.clear();

    if (i > 0)
        read(i);
}

bool Ticket::read(int i)
{
    QSqlQuery q;

    id = i;

    q.prepare("SELECT id, i_id, tm, title, message FROM tickets WHERE id = :id");
    q.bindValue(":id", id);
    if (!q.exec()) {
        qDebug() << q.lastError();
        return false;
    }
    if (q.next()) {
        id = q.value(0).toInt();
        i_id = q.value(1).toInt();
        time = q.value(2).toDateTime();
        title = q.value(3).toString();
        descr = q.value(4).toString();
        return true;
    }

    return false;
}

bool Ticket::Insert()
{
    QSqlQuery q;

    q.prepare("INSERT INTO tickets(i_id, tm, title, message) VALUES(:iid, :tm, :title, :descr)");
    q.bindValue(":iid", i_id);
    q.bindValue(":tm", time);
    q.bindValue(":title", title);
    q.bindValue(":descr", descr);
    if (!q.exec()) {
        qDebug() << q.lastError();
        return false;
    }
    return true;
}

bool Ticket::Remove()
{
    QSqlQuery q;

    if (!id)
        return false;

    q.prepare("DELETE FROM tickets WHERE id = :id");
    q.bindValue(":id", id);
    if (!q.exec()) {
        qDebug() << q.lastError();
        return false;
    }
    return true;
}

ListTicketsModel::ListTicketsModel(int id, QObject *parent) :
    QAbstractTableModel(parent)
{
    pid = id;
    header_data << tr("Дата") << tr("Сообщение");
    read_list(id);
}

int ListTicketsModel::rowCount(const QModelIndex &parent) const
{
    return list.size();
}

int ListTicketsModel::columnCount(const QModelIndex &parent) const
{
    return header_data.size();
}

QVariant ListTicketsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        int row = index.row();
        int col = index.column();
        Ticket t = list.at(row);
        if (col == 0)
            return t.Time();
        if (col == 1)
            return t.Title();
        return QVariant();
    }

    return QVariant();
}

QVariant ListTicketsModel::headerData(int section, Qt::Orientation orientation, int role) const
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

void ListTicketsModel::read_list(int id)
{
    QSqlQuery q;

    list.clear();

    q.prepare("SELECT id FROM tickets WHERE i_id = :id ORDER BY tm");
    q.bindValue(":id", id);
    if (!q.exec()) {
        qDebug() << q.lastError();
        return;
    }
    while (q.next()) {
        Ticket t(q.value(0).toInt());
        list.push_back(t);
    }
}

void ListTicketsModel::updateList()
{
    beginResetModel();
    read_list(pid);
    endResetModel();
}

ListTickets::ListTickets(int id, QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    pid = id;

    Item item(pid);

    label->setText(item.Name());

    model = new ListTicketsModel(id, this);
    connect(this, SIGNAL(updateList()), model, SLOT(updateList()));

    treeView->setModel(model);
    treeView->setAlternatingRowColors(true);
//    treeView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
//    treeView->verticalHeader()->setDefaultSectionSize(tableView->verticalHeader()->minimumSectionSize());
//    treeView->horizontalHeader()->setStretchLastSection(true);
    treeView->setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(treeView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), SLOT(selectionChange()));

    setWindowTitle(tr("Заметки"));

    QAction *ins = new QAction(tr("Добавить"), this);
    ins->setObjectName("add");
    ins->setShortcut(QKeySequence::New);
    connect(ins, &QAction::triggered, this, &ListTickets::addRecord);
    treeView->addAction(ins);

    QAction *rmv = new QAction(tr("Удалить"), this);
    rmv->setObjectName("remove");
    rmv->setShortcut(QKeySequence::Delete);
    rmv->setEnabled(false);
    connect(rmv, &QAction::triggered, this, &ListTickets::delRecord);
    treeView->addAction(rmv);

    treeView->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void ListTickets::addRecord()
{
    EditTicket *et = new EditTicket(this);

    if (et->exec()) {
        Ticket t;
        t.setPId(pid);
        t.setTitle(et->Title());
        t.setDescr(et->Descr());
        if (t.Insert())
            emit updateList();
    }

    QAction *act = findChild<QAction*>("remove");
    if (act) {
        act->setEnabled(false);
    }
}

void ListTickets::delRecord()
{
    int id = model->key(treeView->currentIndex().row());

    if (!id)
        return;

    Ticket t(id);

    int n = QMessageBox::question(this,
                                  tr("Удаление"),
                                  tr("Удалить заметку '%1'?").arg(t.Title()));

    if (n) {
        if (t.Remove())
            emit updateList();
    }
}

void ListTickets::selectionChange()
{
    int row = treeView->selectionModel()->currentIndex().row();
    int id = model->key(row);
    Ticket t(id);

    qDebug() << row << id;

    textBrowser->setText(t.Descr());

    QAction *act = findChild<QAction*>("remove");
    if (act)
        act->setEnabled(true);
}
