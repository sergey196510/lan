#include "exportdata.h"

ExportData::ExportData(QAbstractTableModel *mdl, QObject *parent) : QObject(parent)
{
    model = mdl;
}

ExportData::~ExportData()
{
    delete ui;
}

QCheckBox *ExportData::create_checkbox(QString name)
{
    QCheckBox *box1 = new QCheckBox(ui);
    box1->setObjectName(name);
    box1->setText(name);
    box1->setChecked(true);

    return box1;
}

QDialog *ExportData::init_dialog(QStringList list)
{
    ui = new QDialog();
    ui->setWindowTitle(tr("Выгрузка данных"));

    QVBoxLayout *vlayout = new QVBoxLayout(ui);

    QLabel *label = new QLabel(ui);
    label->setText(tr("Какие колонки выгрузить?"));
    vlayout->addWidget(label);

    for (int i = 0; i < list.size(); i++)
        vlayout->addWidget(create_checkbox(list.at(i)));
//    vlayout->addWidget(create_checkbox("Name"));

    QHBoxLayout *splitLayout = new QHBoxLayout(ui);

    QLabel *label2 = new QLabel(ui);
    label2->setText("Разделитель:");
    splitLayout->addWidget(label2);

    QLineEdit *splitEdit = new QLineEdit(ui);
    splitEdit->setText(";");
    splitEdit->setObjectName("Split");
    splitLayout->addWidget(splitEdit);

    vlayout->addLayout(splitLayout);

    QHBoxLayout *hlayout = new QHBoxLayout(ui);

    QPushButton *okButton = new QPushButton(ui);
    okButton->setText(tr("Ok"));
    connect(okButton, SIGNAL(clicked(bool)), ui, SLOT(accept()));
    hlayout->addWidget(okButton);

    QPushButton *cancelButton = new QPushButton(ui);
    cancelButton->setText(tr("Отмена"));
    connect(cancelButton, SIGNAL(clicked(bool)), ui, SLOT(reject()));
    hlayout->addWidget(cancelButton);

    vlayout->addLayout(hlayout);

    ui->setLayout(vlayout);

    return ui;
}

void ExportData::exportToCSV()
{
    int rows = model->rowCount();
    int cols = model->columnCount();
    QStringList list;
    QString strfilter;
    QString str;

    for (int i = 0; i < cols; i++)
        list.append(model->headerData(i,Qt::Horizontal).toString());

    init_dialog(list);
    if (!ui->exec())
        return;

    QString strfile = QFileDialog::getSaveFileName(0,
                                                   tr("Save as ..."),
                                                   "",
                                                   tr("CSV Files (*.csv)"),
                                                   &strfilter);

    if (strfile.length() == 0)
        return;

    QFile file(strfile);

    if (!file.open(QIODevice::WriteOnly))
        return;

    QString split;
    QLineEdit *led = ui->findChild<QLineEdit*>("Split");
    if (led)
        split = led->text();

    bool k = false;
    for (int i = 0; i < list.size(); i++) {
        QCheckBox *box = ui->findChild<QCheckBox*>(list.at(i));
        if (box->isChecked()) {
            if (k == true)
                str += split /*";"*/;
            k = true;
            str += "\""+list.at(i)+"\"";
            //            qDebug() << list.at(i);
        }
    }
    str += "\n";
    file.write(str.toUtf8());

    for (int i = 0; i < rows; i++) {
        str = "";
        k = false;
        for (int j = 0; j < list.size(); j++) {
            QCheckBox *box = ui->findChild<QCheckBox*>(list.at(j));
            if (box->isChecked()) {
                if (k == true)
                    str += split/*";"*/;
                k = true;
                QString data = model->data(model->index(i,j)).toString();
                str += "\""+data+"\"";
                //                qDebug() << i << j << data;
            }
        }
        str += "\n";
        file.write(str.toUtf8());
    }

    file.close();
}
