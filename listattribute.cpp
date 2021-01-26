#include "listattribute.h"
#include "ui_listattribute.h"

listAttributeModel::listAttributeModel(int type, QObject *parent) :
    QAbstractTableModel(parent)
{
//    header_data << "" << tr("Name") << tr("Status");
//    read_list(type);
    ad = new AttributeData(type);
}

listAttributeModel::~listAttributeModel()
{
    delete ad;
}

void listAttributeModel::reload_data(int type)
{
    beginResetModel();
    ad->read_list(type);
    endResetModel();
}

QVariant listAttributeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        if (index.column() >= 0 || index.column() <= 2) {
            return ad->value(index.row(), index.column());
//            Attribute a = list.at(index.row());
//            return a.Id();
        }
        /*
        if (index.column() == 1) {
            Attribute a = list.at(index.row());
            return a.Name();
        }
        if (index.column() == 2) {
            Attribute a = list.at(index.row());
//            qDebug() << a.Flag() << a.Name();
            if (a.Passive())
                return tr("Removed");
            return QVariant();
        }
        */
    }

    if (role == Qt::TextColorRole) {
//        Attribute a = list.at(index.row());
        if (ad->isPassive(index.row()))
            return QVariant(QColor(Qt::gray));
    }

    return QVariant();
}

QVariant listAttributeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return ad->hedaerValue(section);
    return QVariant();
}

int listAttributeModel::columnCount(const QModelIndex &parent) const
{
    return ad->columnCount();
//    return header_data.size();
}

int listAttributeModel::rowCount(const QModelIndex &parent) const
{
    return ad->rowCount();
}

listAttribute::listAttribute(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::listAttribute)
{
    ui->setupUi(this);

    ui->typeBox->addItem(tr("User"),    LObject::User);
    ui->typeBox->addItem(tr("Address"), LObject::Address);
    ui->typeBox->addItem(tr("Mol"),     LObject::Mol);
    ui->typeBox->addItem(tr("Payment"), LObject::Schet);

    connect(ui->newButton, SIGNAL(clicked(bool)), SLOT(insert()));
    connect(ui->editButton, SIGNAL(clicked(bool)), SLOT(edit()));
    connect(ui->deleteButton, SIGNAL(clicked(bool)), SLOT(remove()));
    connect(ui->recoverButton, SIGNAL(clicked(bool)), SLOT(recovery()));
    connect(ui->typeBox, SIGNAL(currentIndexChanged(int)), SLOT(change_type()));
    connect(ui->closeButton, SIGNAL(clicked(bool)), SLOT(accept()));

    ui->editButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);
    ui->recoverButton->setEnabled(false);

    model = new listAttributeModel(ui->typeBox->Value().toInt(), this);
    ui->tableView->setModel(model);
    ui->tableView->setAlternatingRowColors(true);
//    ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
//    ui->tableView->verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
//    ui->tableView->horizontalHeader()->setSectionResizeMode(4,QHeaderView::Stretch);
//    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->verticalHeader()->setDefaultSectionSize(ui->tableView->verticalHeader()->minimumSectionSize());
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(ui->tableView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), SLOT(change_line()));

    setWindowTitle(tr("Attributes"));
}

listAttribute::~listAttribute()
{
    delete ui;
}

int listAttribute::get_selected_id()
{
    QModelIndexList list;
    QModelIndex idx;
    int l;
    int row = ui->tableView->currentIndex().row();

    if (row >= model->size())
        return 0;

    return model->key(row);
}

void listAttribute::change_type()
{
    model->reload_data(ui->typeBox->Value().toInt());
}

void listAttribute::change_line()
{
    Attribute a(get_selected_id());

    ui->editButton->setEnabled(true);
    ui->deleteButton->setEnabled(!a.Passive());
    ui->recoverButton->setEnabled(a.Passive());
}

void listAttribute::insert()
{
    EditAttribute ea("", ui->typeBox->Value().toInt());

    if (ea.exec()) {
        Attribute a = ea.Value();
        if (a.Insert()) {
            change_type();
            ui->editButton->setEnabled(false);
            ui->deleteButton->setEnabled(false);
            ui->recoverButton->setEnabled(false);
            emit changeAttribute(a.Type());
        }
    }
}

void listAttribute::edit()
{
    EditAttribute ea("", ui->typeBox->Value().toInt());

    int id = get_selected_id();
    if (id == 0)
        return;
    Attribute a(id);

    ea.setValue(a);
    if (ea.exec() == QDialog::Accepted) {
        a = ea.Value();
        a.setId(id);
        if (a.Update()) {
            change_type();
            ui->editButton->setEnabled(false);
            ui->deleteButton->setEnabled(false);
            ui->recoverButton->setEnabled(false);
            emit changeAttribute(a.Type());
        }
    }
}

void listAttribute::remove()
{
    int id = get_selected_id();
    if (id == 0)
        return;
    Attribute a(id);

    int n = QMessageBox::question(this, tr("Remove"), tr("Remove attribute:\n")+a.Name());
    if (n != QMessageBox::Yes)
        return;

    if (a.checkItem()) {
        QMessageBox::warning(this, tr("Warning"), tr("This attribute not empty"));
        return;
    }

    if (a.setPassive()) {
        change_type();
        ui->editButton->setEnabled(false);
        ui->deleteButton->setEnabled(false);
        ui->recoverButton->setEnabled(false);
        emit changeAttribute(a.Type());
    }
}

void listAttribute::recovery()
{
    int id = get_selected_id();
    if (id == 0)
        return;
    Attribute a(id);

    int n = QMessageBox::question(this, tr("Recovery"), tr("Recovery attribute:\n")+a.Name());
    if (n != QMessageBox::Yes)
        return;

    if (a.setActive()) {
        change_type();
        ui->editButton->setEnabled(false);
        ui->deleteButton->setEnabled(false);
        ui->recoverButton->setEnabled(false);
        emit changeAttribute(a.Type());
    }
}
