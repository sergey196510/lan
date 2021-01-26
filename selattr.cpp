#include "selattr.h"
#include "ui_selattr.h"

SelAttr::SelAttr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelAttr)
{
    ui->setupUi(this);

    ui->dateEdit->setCalendarPopup(true);
    ui->dateEdit->setDate(QDate::currentDate());

//    ui->user->read_data(LObject::User);
//    ui->address->read_data(LObject::Address);
//    ui->mol->read_data(LObject::Mol);

//    connect(ui->mol, SIGNAL(Updated(int)), SLOT(change_mol()));
//    connect(ui->mol, SIGNAL(change_data()), SIGNAL(updateAttribute()));
    connect(ui->fileButton, SIGNAL(clicked()), SLOT(selectFile()));

    connect(ui->okButton, SIGNAL(clicked()), SLOT(pressOk()));
    connect(ui->cancelButton, SIGNAL(clicked()), SLOT(reject()));
}

SelAttr::~SelAttr()
{
    delete ui;
}

void SelAttr::setData(grAttr ga)
{
 //   grAttr attr;
 //   ui->title->setText("("+i.Cod()+") "+i.Name());

 //   attr.Read(i.Id());
    ui->widget->setData(ga);

//    ui->widget
//    ui->mol->setValue(i.Attribute().Mol());
//    ui->address->setValue(i.Attribute().Address());
//    ui->user->setValue(i.Attribute().User());
}

grAttr SelAttr::Attr()
{
    return ui->widget->Data();
}

QVariant SelAttr::Mol()
{
    grAttr attr = ui->widget->Data();
    return attr.Mol();
//    return ui->mol->Value();
}

QVariant SelAttr::User()
{
    grAttr attr = ui->widget->Data();
    return attr.User();
//    return ui->user->Value();
}

QVariant SelAttr::Address()
{
    grAttr attr = ui->widget->Data();
    return attr.Address();
//    return ui->address->Value();
}

QDate SelAttr::Date()
{
    return ui->dateEdit->date();
}

QString SelAttr::Description()
{
    return ui->descrEdit->text();
}

QString SelAttr::fileName()
{
    return ui->fileEdit->text();
}

void SelAttr::selectFile()
{
//    QString strFilter;
    QString str = QFileDialog::getOpenFileName(0, tr("Load"), "", "*.pdf *.doc *.xls");
    ui->fileEdit->setText(str);
}

/*
void SelAttr::change_mol()
{
//        Attribute a(ui->mol->Value().toInt());
//        a.Read(ui->mol->Value().toInt());

//        ui->label_4->setEnabled(a.Aist());
//        ui->label_5->setEnabled(a.Aist());
//        ui->user->setEnabled(a.Aist());
//        ui->address->setEnabled(a.Aist());
//        if (!a.Aist()) {
//            ui->user->setValue(0);
//            ui->address->setValue(0);
//        }

        emit updateAttribute();
}
*/

void SelAttr::pressOk()
{
    int mol = Mol().toInt();
    Attribute a;

    a.Read(mol);
    if (a.Aist() && (!User().toInt() || !Address().toInt())) {
        QMessageBox::critical(this, tr("Ошибка"), tr("Пользователь или адрес не выбраны"));
        return;
    }
    else
        accept();
}
