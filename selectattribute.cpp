#include "selectattribute.h"
#include "ui_selectattribute.h"

SelectAttribute::SelectAttribute(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SelectAttribute)
{
    type = 0;
    ui->setupUi(this);

//    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    ui->verticalLayout->setMargin(0);
    ui->horizontalLayout_3->setMargin(0);

//    connect(ui->toolButton, SIGNAL(clicked()), SLOT(insert_value())); // вставляем новый элемент
    connect(ui->newButton, &QToolButton::clicked, this, &SelectAttribute::insert_value);
//    connect(this, SIGNAL(change_data()), ui->comboBox, SLOT(reload_data())); // сообщаем что список изменился
//    connect(ui->delButton, &QToolButton::clicked, this, &SelectAttribute::delete_value);
    connect(this, &SelectAttribute::change_data, ui->comboBox, &LComboBox::reload_data);
    connect(ui->comboBox, SIGNAL(Updated()), SLOT(attrUpdated())); // получили сигнал о том что список перезагружен
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), SIGNAL(Updated(int))); // изменился текущий элемент
//    connect(ui->comboBox, &LComboBox::currentIndexChanged, this, &SelectAttribute::Updated);
}

SelectAttribute::~SelectAttribute()
{
    delete ui;
}

void SelectAttribute::read_data(int t)
{
    type = t;
//    ui->label->setText(name);
    ui->comboBox->read_data(type);
}

void SelectAttribute::setValue(int val)
{
    ui->comboBox->setValue(val);
}

QVariant SelectAttribute::Value()
{
    return ui->comboBox->Value();
}

void SelectAttribute::insert_value()
{
    EditAttribute ea("", type);

    if (ea.exec()) {
        Attribute attr;
        attr = ea.Value();
        id = attr.Insert();
        emit change_data();
    }
}

void SelectAttribute::attrUpdated()
{
    ui->comboBox->setValue(id);
    emit Updated(id);
}

/*
void SelectAttribute::delete_value()
{
    QSqlQuery q;
    int val = ui->comboBox->Value().toInt();

    q.prepare("SELECT count(id) FROM attr_link WHERE a_id = :id AND active = 1");
    q.bindValue(":id", val);
    if (!q.exec()) {
        qDebug() << q.lastError();
        return;
    }
    if (!q.next()) {
        return;
    }
    int num = q.value(0).toInt();
    qDebug() << "delete value:" << val << num;

    if (num > 0) {
        QMessageBox::critical(this, tr("Error"), tr("You can't delete attribute\nYou must move all item from this attribute!"));
        return;
    }

    emit Updated(id);
}
*/
