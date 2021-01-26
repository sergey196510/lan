#include "editattribute.h"
#include "ui_editattribute.h"

EditAttribute::EditAttribute(QString str, int t, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditAttribute)
{
    ui->setupUi(this);

    type = t;

    types << "" << tr("Пользователь") << tr("Адрес") << tr("МОЛ") << tr("Счет");

    ui->typeLabel->setText(types.at(type));

    ui->checkBox->setToolTip(tr("Разрешить или запретить выбирать пользователя и адрес при выборе этого %1").arg(types.at(type)));
    if (type == 3) {
        QCheckBox *checkbox = new QCheckBox(this);
        checkbox->setObjectName("auto");
        checkbox->setText(tr("Автоматически"));
        checkbox->setToolTip(tr("Выбирать этот %1 при выборе пользователя").arg(types.at(type)));
        ui->formLayout->setWidget(2, QFormLayout::FieldRole, checkbox);
    }

    ui->nameEdit->setText(str);

    if (type != 3)
        ui->checkBox->setVisible(false);

    connect(ui->okButton, SIGNAL(clicked()), SLOT(accept()));
    connect(ui->cancelButton, SIGNAL(clicked()), SLOT(reject()));
}

EditAttribute::~EditAttribute()
{
    delete ui;
}

void EditAttribute::setValue(Attribute attr)
{
    ui->nameEdit->setText(attr.Name());
    ui->checkBox->setChecked(attr.Aist());
    QCheckBox *box = findChild<QCheckBox*>("auto");
    if (box)
        box->setChecked(attr.defaultUser());
}

Attribute EditAttribute::Value()
{
    Attribute attr;

    attr.setName(ui->nameEdit->text());
    attr.setType(type);

    if (ui->checkBox->isChecked())
        attr.setAist();
//    attr.setFlag(ui->checkBox->isChecked());

    QCheckBox *box = findChild<QCheckBox*>("auto");
    if (box && box->isChecked())
            attr.setDefaultUser();

    return attr;
}
