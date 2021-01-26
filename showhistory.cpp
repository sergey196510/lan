#include "showhistory.h"

showHistory::showHistory(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);

    setWindowTitle(tr("История"));

    connect(ui.saveasButton, SIGNAL(clicked(bool)), SLOT(saveas()));
    connect(ui.pushButton, SIGNAL(clicked()), SLOT(close()));
}

void showHistory::setText(QString str)
{
    ui.textBrowser->setText(str);
}

void showHistory::saveas()
{
    QString str = QFileDialog::getSaveFileName(this, tr("Сохранить как"), "", "*.pdf");
    if (str.isEmpty())
        return;

//    QTextEdit* ptxt = new QTextEdit("This is a <b>TEST</b>");
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(str);
    ui.textBrowser->document()->print(&printer);
}
