#include "edititem.h"
#include "ui_edititem.h"
#include "address.h"

EditItem::EditItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditItem)
{
    ui->setupUi(this);

    ui->title->setText(tr("Insert new item"));

    ui->dateEdit->setCalendarPopup(true);
    ui->dateEdit->setDate(QDate::currentDate());

    connect(ui->codEdit, SIGNAL(editingFinished()), SLOT(check_cod()));

    connect(ui->okButton, SIGNAL(clicked()), SLOT(pressOk()));
    connect(ui->cancelButton, SIGNAL(clicked()), SLOT(reject()));

    connect(ui->attribute, SIGNAL(updatedAttribute()), this, SIGNAL(updateAttribute()));
}

EditItem::~EditItem()
{
    delete ui;
}

void EditItem::check_cod()
{
    QSqlQuery q;
    Item it;

    if (it.read_by_cod(ui->codEdit->text()) == true) {
        Attribute a(it.Attribute().Mol());

        ui->nameEdit->setText(it.Name());
        ui->attribute->setData(it.Attribute());
    }
//    else {
//        grAttr ga;
//        ui->nameEdit->clear();
//        ui->attribute->setData(ga);
//    }
}

Item EditItem::data()
{
    Item data;
    grAttr ga = ui->attribute->Data();

    data.setCod(ui->codEdit->text());
    data.setName(ui->nameEdit->text());
//    ga = ui->attribute->Data();

    data.setAttr(ga);
    data.setDate(ui->dateEdit->date());
    data.setDescr(ui->descrEdit->text());

    return data;
}

void EditItem::setUser(int user)
{
    grAttr ga;
    ga.setData(user,0,0,0);
    ui->attribute->setData(ga);
}

void EditItem::pressOk()
{
    grAttr ga = ui->attribute->Data();
    Attribute a;

    a.Read(ga.Mol());
    if (a.Aist() && (!ga.User() || !ga.Address())) {
        QMessageBox::critical(this, tr("Ошибка"), tr("Пользователь или адрес не выбраны"));
        return;
    }
    else
        accept();
}
