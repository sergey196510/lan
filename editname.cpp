#include "editname.h"
#include "ui_editname.h"

EditName::EditName(QString str, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditName)
{
    ui->setupUi(this);

    setValue(str);

    connect(ui->okButton, SIGNAL(clicked()), SLOT(accept()));
    connect(ui->cancelButton, SIGNAL(clicked()), SLOT(reject()));
}

EditName::~EditName()
{
    delete ui;
}

QString EditName::Value()
{
    return ui->nameEdit->text();
}

void EditName::setValue(QString str)
{
    ui->nameEdit->setText(str);
}
