#include "wgrattr.h"
#include "ui_wgrattr.h"

WGrAttr::WGrAttr(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WGrAttr)
{
    ui->setupUi(this);

    ui->user->read_data(LObject::User);
    ui->address->read_data(LObject::Address);
    ui->mol->read_data(LObject::Mol);
    ui->schet->read_data(LObject::Schet);

    connect(ui->user, &SelectAttribute::Updated, this, &WGrAttr::changeUser);
    connect(ui->mol, &SelectAttribute::Updated, this, &WGrAttr::changeMol);

    connect(ui->user,    SIGNAL(change_data()), SIGNAL(updatedAttribute()));
    connect(ui->mol,     SIGNAL(change_data()), SIGNAL(updatedAttribute()));
    connect(ui->schet,   SIGNAL(change_data()), SIGNAL(updatedAttribute()));
    connect(ui->address, SIGNAL(change_data()), SIGNAL(updatedAttribute()));
}

WGrAttr::~WGrAttr()
{
    delete ui;
}

void WGrAttr::setData(grAttr attr)
{
    ui->user->setValue(attr.User());
    ui->address->setValue(attr.Address());
    ui->mol->setValue(attr.Mol());
    ui->schet->setValue(attr.Schet());
}

grAttr WGrAttr::Data()
{
    grAttr attr;

    attr.setData(ui->user->Value().toInt(), ui->address->Value().toInt(), ui->mol->Value().toInt(), ui->schet->Value().toInt());

    return attr;
}

void WGrAttr::changeUser()
{
    int user = ui->user->Value().toInt();
    int mol = ui->mol->Value().toInt();

    if (user && mol == 0) {
        Attribute mol(Attribute().getDefaultUser(3));
        ui->mol->setValue(mol.Id());
    }
}

void WGrAttr::changeMol()
{
    Attribute a;

    a.Read(ui->mol->Value().toInt());

    ui->user->setEnabled(a.Aist());
    ui->address->setEnabled(a.Aist());

    if (!a.Aist()) {
        ui->user->setValue(0);
        ui->address->setValue(0);
    }
}
