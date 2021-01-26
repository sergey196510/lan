#include "listitems.h"
#include "ui_listitems.h"

ListItemsModel::ListItemsModel(QObject *parent) :
    QAbstractTableModel(parent)
{
    attrSearch as;

    header_data <<
                   tr("Код") <<
                   tr("Наименование") <<
                   tr("Адрес") <<
                   tr("Счет") <<
                   tr("МОЛ") <<
                   tr("Пользователь");
    list = read_list(as);
}

ListItemsModel::~ListItemsModel()
{

}

QList<Item> ListItemsModel::read_list(attrSearch as)
{
    QSqlQuery q;

    q.prepare("SELECT id FROM item ORDER BY name");
    if (!q.exec()) {
        qDebug() << q.lastError();
        return list;
    }

    while (q.next()) {
        Item i(q.value(0).toInt());
        if (as.mol && i.Attribute().Mol() != as.mol)
            continue;
        if (as.addr && i.Attribute().Address() != as.addr)
            continue;
        if (as.user && i.Attribute().User() != as.user)
            continue;
        list.append(i);
    }

    return list;
}

int ListItemsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return list.size();
}

int ListItemsModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return header_data.size();
}

QVariant ListItemsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        Item i = list.at(index.row());
        if (index.column() == 0) {
            return i.Cod();
        }
        if (index.column() == 1) {
            return i.Name();
        }
        if (index.column() == 2) {
            Link l;
            if (l.findActive(i.Id(),LObject::Address)) {
                Attribute a(l.Attr());
                return a.Name();
            }
        }
        if (index.column() == 3) {
            Link l;
            if (l.findActive(i.Id(),LObject::Schet)) {
                Attribute a(l.Attr());
                return a.Name();
            }
        }
        if (index.column() == 4) {
            Link l;
            if (l.findActive(i.Id(),LObject::Mol)) {
                Attribute a(l.Attr());
                return a.Name();
            }
        }
        if (index.column() == 5) {
            Link l;
            if (l.findActive(i.Id(),LObject::User)) {
                Attribute a(l.Attr());
                return a.Name();
            }
        }
        return QVariant();
    }

    if (role == Qt::ToolTipRole) {
        Item i = list.at(index.row());
        return i.Name();
    }

    return QVariant();
}

QVariant ListItemsModel::headerData(int section, Qt::Orientation orientation, int role) const
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

void ListItemsModel::reload_list(attrSearch as)
{
    beginResetModel();
    list.clear();
    read_list(as);
    if (sortcolumn)
        sort(sortcolumn, sortorder);
    endResetModel();
}

int ListItemsModel::key(int row)
{
    return list[row].Id();
}

QVariant ListItemsModel::item(int row, int col)
{
    if (row >= list.size() || col >= header_data.size())
        return QVariant();

    Item it = list.at(row);
    Link l;
    switch (col) {
    case 0:
        return it.Cod();
        break;
    case 1:
        return it.Name();
        break;
    case 2:
        if (l.findActive(it.Id(),LObject::Address)) {
            Attribute a(l.Attr());
            return a.Name();
        }
        break;
    case 3:
        if (l.findActive(it.Id(),LObject::Schet)) {
            Attribute a(l.Attr());
            return a.Name();
        }
        break;
    case 4:
        if (l.findActive(it.Id(),LObject::Mol)) {
            Attribute a(l.Attr());
            return a.Name();
        }
        break;
    case 5:
        if (l.findActive(it.Id(),LObject::User)) {
            Attribute a(l.Attr());
            return a.Name();
        }
        break;
    default:
        break;
    }

    return QVariant();
}

bool ListItemsModel::compare(QVariant f, QVariant l, Qt::SortOrder order)
{
    if (order == 1) {
        if (f.toString() < l.toString())
            return true;
        return false;
    }
    else
        if (l.toString() < f.toString())
            return true;

    return false;
}

void ListItemsModel::sort(int col, Qt::SortOrder order)
{
    int f = 0, l = list.size();
    int i, mi;
    bool flag;

//    qDebug() << "sort" << col;

    sortcolumn = col;
    sortorder = order;

    beginResetModel();

    for (f = 0; f < l-1; f++) {
        QVariant value = item(f, col);
        flag = false;
        for (i = f+1; i < l; i++) {
            QVariant val = item(i, col);
            if (compare(value, val, order)) {
//            if (val < value) {
                value = val;
                mi = i;
                flag = true;
            }
        }
        if (flag == true) {
            list.swap(f, mi);
        }
        qApp->processEvents();
    }

    endResetModel();
}

ListItems::ListItems(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListItems)
{
    ui->setupUi(this);

    s = 0;

//    ui->codEdit->setText("%");
    update_attribute();

    ui->moveButton->setEnabled(false);

    model = new ListItemsModel(this);
    ui->tableView->setModel(model);
//    ui->tableView->hideColumn(0);
    ui->tableView->setAlternatingRowColors(true);
//    ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
//    ui->tableView->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
//    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
//    ui->tableView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
//    ui->tableView->horizontalHeader()->setSectionResizeMode(4,QHeaderView::Stretch);
//    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
//    ui->tableView->verticalHeader()->setDefaultSectionSize(ui->tableView->verticalHeader()->minimumSectionSize());
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::MultiSelection);

    ui->tableView->setSortingEnabled(true);
//    ui->tableView->horizontalHeader()->setSortIndicator(1, Qt::AscendingOrder);
//    connect(ui->tableView->horizontalHeader(), SIGNAL(sortIndicatorChanged(int,Qt::SortOrder)), model, SLOT(sort(int,Qt::SortOrder)));

    connect(ui->molBox, SIGNAL(currentIndexChanged(int)), SLOT(select_attr(int)));
    connect(ui->addrBox, SIGNAL(currentIndexChanged(int)), SLOT(select_attr(int)));
    connect(ui->userBox, SIGNAL(currentIndexChanged(int)), SLOT(select_attr(int)));
    connect(ui->moveButton, SIGNAL(clicked()), SLOT(hist_user()));
    connect(this, SIGNAL(reload_list(attrSearch)), model, SLOT(reload_list(attrSearch)));

    QAction *separator = new QAction(this);
    separator->setSeparator(true);

    QAction *cb = new QAction(tr("Копировать"), this);
    cb->setShortcut(tr("Ctrl+C"));
    connect(cb, SIGNAL(triggered()), SLOT(copy_text()));
    acts.append(cb);

    acts.append(separator);

    QAction *sh = new QAction(tr("Поиск"), this);
    sh->setShortcut(tr("Ctrl+F"));
    connect(sh, SIGNAL(triggered()), SLOT(search_text()));
    acts.append(sh);

    QAction *hs = new QAction(tr("История"), this);
    connect(hs, SIGNAL(triggered()), SLOT(history()));
    acts.append(hs);

    QAction *hs2 = new QAction(tr("История new"), this);
    connect(hs2, SIGNAL(triggered()), SLOT(history2()));
    acts.append(hs2);

    acts.append(separator);

    QAction *cu = new QAction(tr("Смена атрибута"), this);
    sh->setShortcut(tr("Ctrl+A"));
    connect(cu, SIGNAL(triggered()), SLOT(change_attribute()));
    acts.append(cu);

    QAction *cd = new QAction(tr("Редактировать код"), this);
    connect(cd, SIGNAL(triggered()), SLOT(update_cod()));
    acts.append(cd);

    QAction *cn = new QAction(tr("Редактировать наименование"), this);
    connect(cn, SIGNAL(triggered()), SLOT(update_name()));
    acts.append(cn);

    QAction *sa = new QAction(tr("Выбрать все"), this);
    sh->setShortcut(tr("Ctrl+S"));
    sa->setShortcut(QKeySequence::SelectAll);
    connect(sa, SIGNAL(triggered(bool)), SLOT(selectAll()));
    acts.append(sa);

    QAction *an = new QAction(tr("Заметки"), this);
    connect(an, SIGNAL(triggered(bool)), SLOT(tickets()));
    acts.append(an);

    ui->tableView->addActions(acts);
    ui->tableView->setContextMenuPolicy(Qt::ActionsContextMenu);

    for (int i = 0; i < ui->tableView->model()->rowCount(); i++) {
        for (int j = 0; j < ui->tableView->model()->columnCount(); j++) {
            QPoint p(j,i);
            point.append(p);
        }
    }

//    select_attr(0);
}

ListItems::~ListItems()
{
    delete model;
    delete ui;
}

void ListItems::select_attr(int idx)
{
    attrSearch as;

    as.mol = ui->molBox->Value().toInt();
    as.addr = ui->addrBox->Value().toInt();
    as.user = ui->userBox->Value().toInt();
    ui->moveButton->setEnabled(as.user);

    emit reload_list(as);
}

void ListItems::update_attr(int idx)
{
    attrSearch as;

    as.mol = ui->molBox->Value().toInt();
    as.addr = ui->addrBox->Value().toInt();
    as.user = ui->userBox->Value().toInt();

    if (idx) {
        if (idx == LObject::User)
            ui->userBox->reload_data();
        if (idx == LObject::Address)
            ui->addrBox->reload_data();
        if (idx == LObject::Mol)
            ui->molBox->reload_data();
    }

    ui->userBox->setValue(as.user);
    ui->addrBox->setValue(as.addr);
    ui->molBox->setValue(as.mol);

    as.mol = ui->molBox->Value().toInt();
    as.addr = ui->addrBox->Value().toInt();
    as.user = ui->userBox->Value().toInt();

    emit reload_list(as);
}

void ListItems::new_record()
{
    EditItem *ei = new EditItem(this);

    connect(ei, SIGNAL(updateAttribute()), SLOT(update_attribute()));

    int user = ui->userBox->Value().toInt();
    if (user)
        ei->setUser(user);

    if (ei->exec()) {
        Item m = ei->data();
        m.insert();
        select_attr(0);
    }
}

void ListItems::update_record()
{

}

void ListItems::delete_record()
{

}

void ListItems::change_attribute()
{
    QSqlQuery q;
//    QAction *action = qobject_cast<QAction*>(sender());
    QString s = sender()->objectName();
    SelAttr *sa = new SelAttr(this);
    QList<int> list_id = get_selected_id();
    Item is, id;

    connect(sa, SIGNAL(updateAttribute()), SLOT(update_attribute()));

    if (list_id.size() == 0)
        return;

    if (list_id.size() == 1) {
        grAttr ga;
        ga.Read(list_id.at(0));
        sa->setData(ga);
    }
    else if (list_id.size() > 1) {
        grAttr ga;
        ga.setData(ui->userBox->Value().toInt(), ui->addrBox->Value().toInt(), ui->molBox->Value().toInt(), 0);
        is.setAttr(ga);
        sa->setData(ga);
    }

    if (sa->exec()) {
        q.exec("BEGIN");
        grAttr attr = sa->Attr();
        QDateTime tm = QDateTime().currentDateTime();

        Link l;
        int id_doc = l.insert_document(sa->fileName());

        for (int i = 0; i < list_id.size(); ++i) {

            is.read_by_id(list_id.at(i));

            l.setData(list_id.at(i), sa->Date(), 1, sa->Description(), id_doc, tm);

//            qDebug() << "User:" << is.Attribute().User() << attr.User();
            if (l.Update(is.Attribute().User(), attr.User(), LObject::User) == false) {
                q.exec("ROLLBACK");
                return;
            }

//            qDebug() << "Address:" << is.Attribute().Address() << attr.Address();
            if (l.Update(is.Attribute().Address(), attr.Address(), LObject::Address) == false) {
                q.exec("ROLLBACK");
                return;
            }

//            qDebug() << "MOL:" << is.Attribute().Mol() << attr.Mol();
            if (l.Update(is.Attribute().Mol(), attr.Mol(), LObject::Mol) == false) {
                q.exec("ROLLBACK");
                return;
            }

        }
        q.exec("COMMIT");
        select_attr(0);
    }

}

QList<int> ListItems::get_selected_id()
{
    QModelIndexList list;
    QModelIndex idx;
    QList<int> l;

//    int id = model->key(ui->tableView->currentIndex().row());
//    l.append(id);
//    return l;

    list = ui->tableView->selectionModel()->selectedIndexes();
    if (list.size() == 0) {
        QMessageBox::critical(this, tr("Операция прервана"), tr("Ничего не выбрано"));
        return l;
    }

    for (int i = 0; i < list.size(); i += model->columnCount(QModelIndex())) {
//        int s = list.at(i).data(Qt::DisplayRole).toInt();
        int r = list.at(i).row();
        int s = model->key(r);
//        qDebug() << s;
        l.append(s);
    }

    return l;
}

void ListItems::update_attribute()
{
    int mol = ui->molBox->Value().toInt();
    int addr = ui->addrBox->Value().toInt();
    int user = ui->userBox->Value().toInt();

    ui->molBox->read_data(LObject::Mol);
    ui->addrBox->read_data(LObject::Address);
    ui->userBox->read_data(LObject::User);

    ui->molBox->setValue(mol);
    ui->addrBox->setValue(addr);
    ui->userBox->setValue(user);
}

/*
void ListItems::check_cod(QString c)
{
    if (c.size() == 0)
        ui->codEdit->setText("%");

    select_attr(0);
}
*/

void ListItems::history()
{
    QSqlQuery q;
    QList<int> l = get_selected_id();
    QString msg;

    if (l.size() != 1) {
        return;
    }

    int id = l.at(0);
    Item it(id);

    msg += "<html><center>";
    msg += it.Cod() + " " + it.Name();
    msg += "<table border=\"1\">";
    msg += "<tr><th>Атрибут</th><th>Наименование</th><th>Установлен</th><th>Демонтирован</th><th>Примечание</th></tr>";

    q.prepare("SELECT a_id, type, bd, ld, descr FROM attr_link WHERE i_id = :id ORDER BY type,bd,ld");
    q.bindValue(":id", id);
    if (!q.exec()) {
//        qDebug() << q.lastError();
        return;
    }
    while (q.next()) {
        Attribute a;
//        qDebug() << id << q.value(0).toInt() << q.value(1).toInt() << q.value(2).toDate() << q.value(3).toDate() << q.value(4).toString();
        msg += "<tr>";
        msg += "<td>";
        if (q.value(1).toInt() == 1)
            msg += tr("Пользователь:");
        if (q.value(1).toInt() == 2)
            msg += tr("Адрес:");
        if (q.value(1).toInt() == 3)
            msg += tr("МОЛ:");
        if (q.value(1).toInt() == 4)
            msg += tr("Счет:");
        msg += "</td>";
        a.Read(q.value(0).toInt());
        msg += "<td>"+a.Name()+"</td>";
        msg += "<td>"+q.value(2).toString()+"</td>";
        msg += "<td>"+q.value(3).toString()+"</td>";
        msg += "<td>"+q.value(4).toString()+"</td>";
//        txt->append(q.value(1).toString()+" "+q.value(0).toString()+" "+q.value(2).toString()+" "+q.value(3).toString()+" "+q.value(4).toString());
//        msg += "\n---------------------------------\n";
        msg += "</tr>";
    }
    msg += "</table>";
    msg += "</center></html>";

    showHistory sh;
    sh.setText(msg);
    sh.exec();

//    QMessageBox::information(this, tr("History"), msg);
}

void ListItems::history2()
{
    QList<int> l = get_selected_id();

    if (l.size() != 1)
        return;
    int id = l.at(0);

    ListMovements lm(new ListMovements2Model(id));
    lm.exec();
}

void ListItems::hist_user()
{
    QSqlQuery q;
    QString msg;
    int uid = ui->userBox->Value().toInt();

    Attribute at(uid);

    msg += "<html><center>";
    msg += tr("История<p>");
    msg += tr("Пользователь: ")+at.Name();
    msg += "<table border=\"1\">";
    msg += "<tr><th>Код</th><th>Наименование</th><th>Установлен</th><th>Демонтирован</th><th>Примечание</th><th>Статус</th></tr>";

    q.prepare("SELECT i_id, active, bd, ld, descr FROM attr_link WHERE a_id = :id AND type = 1 ORDER BY bd,ld");
    q.bindValue(":id", uid);
    if (!q.exec()) {
//        qDebug() << q.lastError();
        return;
    }
    while (q.next()) {
        Item i;
//        qDebug() << uid << q.value(0).toInt() << q.value(1).toInt() << q.value(2).toDate() << q.value(3).toDate() << q.value(4).toString();
        msg += "<tr>";
//        msg += tr("<td>Device</td>");
        i.read_by_id(q.value(0).toInt());
        msg += "<td>"+i.Cod()+"</td>";
        msg += "<td>"+i.Name()+"</td>";
        msg += "<td>"+q.value(2).toString()+"</td>";
        msg += "<td>"+q.value(3).toString()+"</td>";
        msg += "<td>"+q.value(4).toString()+"</td>";
        msg += (q.value(1).toInt()) ? "<td>Установлен</td>" : "<td>Демонтирован</td>";
//        txt->append(q.value(1).toString()+" "+q.value(0).toString()+" "+q.value(2).toString()+" "+q.value(3).toString()+" "+q.value(4).toString());
//        msg += "\n---------------------------------\n";
        msg += "</tr>";
    }
    msg += "</table>";
    msg += "</center></html>";

    showHistory sh;
    sh.setText(msg);
    sh.exec();

//    QMessageBox::information(this, tr("History"), msg);
}

void ListItems::search_text()
{
    if (!s) {
        s = new Search(this);
        connect(s, SIGNAL(firstClick(int,QString)), SLOT(search_first(int,QString)));
        connect(s, SIGNAL(prevClick()), SLOT(search_prev()));
        connect(s, SIGNAL(nextClick()), SLOT(search_next()));
        connect(s, SIGNAL(lastClick()), SLOT(search_last()));
        connect(this, SIGNAL(SearchFirst(int,int)), s, SLOT(SearchFirst(int,int)));
    }

//    s->exec();
    s->show();
    s->raise();
    s->activateWindow();
}

void ListItems::search_first(int key, QString str)
{
    int col = 0;
    int flag = 0;

    if (str.length() == 0)
        return;

    if (key == 1)
        col = 0;
    else if (key == 2)
        col = 1;
    indexes = ui->tableView->model()->match(ui->tableView->model()->index(0, col), Qt::DisplayRole, str, -1, Qt::MatchFlags(Qt::MatchRecursive | Qt::MatchExactly | Qt::MatchFixedString | Qt::MatchWrap | Qt::MatchStartsWith));

    ui->tableView->clearSelection();
    if (indexes.size()) {
        idx = indexes.begin();
//        for (; idx != indexes.end(); ++idx)
//            qDebug() << ui->tableView->model()->data(*idx, Qt::DisplayRole);
        ui->tableView->clearSelection();
        idx = indexes.begin();
        ui->tableView->setCurrentIndex(*idx);
    }

    if (idx == indexes.begin())
        flag = 1;
    else if (idx == indexes.end())
        flag = 2;

    emit SearchFirst(indexes.size(),flag);
}

void ListItems::search_prev()
{
    int flag = 0;

    if (indexes.size() && idx != indexes.begin()) {
        --idx;
        ui->tableView->clearSelection();
        ui->tableView->setCurrentIndex(*idx);
    }

    if (idx == indexes.begin())
        flag = 1;
    else if (idx == indexes.end())
        flag = 2;

    emit SearchFirst(indexes.size(),flag);
}

void ListItems::search_next()
{
    int flag = 0;

    if (!indexes.size()) {
        emit SearchFirst(indexes.size(),flag);
        return;
    }

    ++idx;
    if (indexes.size() && idx != indexes.end()) {
        ui->tableView->clearSelection();
        ui->tableView->setCurrentIndex(*idx);
    }

    if (idx == indexes.begin())
        flag = 1;
    else if (idx == indexes.end())
        flag = 2;

    emit SearchFirst(indexes.size(),flag);
}

void ListItems::search_last()
{
    int flag = 0;

    if (indexes.size() && idx != indexes.end()) {
        idx = indexes.end();
        --idx;
        ui->tableView->clearSelection();
        ui->tableView->setCurrentIndex(*idx);
    }

    if (idx == indexes.begin())
        flag = 1;
    else if (idx == indexes.end())
        flag = 2;

    emit SearchFirst(indexes.size(),flag);
}

void ListItems::update_cod()
{
    QSqlQuery q;
    QList<int> l = get_selected_id();
    Item it;
    EditName en("");
    bool ok;

    if (l.size() != 1)
        return;

    it.read_by_id(l.at(0));

    QString cod = QInputDialog::getText(this, tr("Cod"), tr("Cod:"), QLineEdit::Normal, it.Cod(), &ok);
    if (ok && !cod.isEmpty()) {
        it.setCod(cod);
        it.update_cod();
        select_attr(0);
    }
}

void ListItems::update_name()
{
    QSqlQuery q;
    QList<int> l = get_selected_id();
    Item it;
    EditName en("");
    bool ok;

    if (l.size() != 1)
        return;

    it.read_by_id(l.at(0));

    QString name = QInputDialog::getText(this, tr("Name"), tr("Name:"), QLineEdit::Normal, it.Name(), &ok);
    if (ok && !name.isEmpty()) {
        it.setName(name);
        it.update_name();
        select_attr(0);
    }
}

// копировать содержимое текущей ячейки в буфер обмена
void ListItems::copy_text()
{
//    QModelIndexList list;
    QModelIndex idx;
    QClipboard *clb = QApplication::clipboard();
//    QList<int> l;

    idx = ui->tableView->currentIndex();
    QString data = ui->tableView->model()->data(idx, Qt::DisplayRole).toString();
    clb->setText(data);
//
//    qDebug() << data;
}

void ListItems::export_data()
{
    ExportData data(model, this);
    data.exportToCSV();
}

void ListItems::selectAll()
{
    QModelIndex tl, br;
    QItemSelectionModel *selectionModel = ui->tableView->selectionModel();

    tl = model->index(0,0, QModelIndex());
    br = model->index(model->rowCount(QModelIndex())-1, model->columnCount(QModelIndex())-1, QModelIndex());

    QItemSelection selection(tl, br);
    selectionModel->select(selection, QItemSelectionModel::Select);
}

void ListItems::tickets()
{
    QList<int> id = get_selected_id();

    if (id.size() != 1)
        return;

    ListTickets *lt = new ListTickets(id.at(0), this);
    lt->exec();
}
