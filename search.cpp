#include "search.h"

Search::Search(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);

    setWindowTitle(tr("Поиск"));

    connect(ui.radioCod, SIGNAL(clicked(bool)), SLOT(firstKey()));
    connect(ui.radioName, SIGNAL(clicked(bool)), SLOT(firstKey()));
    connect(ui.searchEdit, SIGNAL(textChanged(QString)), SLOT(firstKey()));
    connect(ui.closeButton, SIGNAL(clicked()), SLOT(close()));
    connect(ui.firstButton, SIGNAL(clicked()), SLOT(firstKey()));
    connect(ui.prevButton, SIGNAL(clicked()), SLOT(prevKey()));
    connect(ui.nextButton, SIGNAL(clicked()), SLOT(nextKey()));
    connect(ui.lastButton, SIGNAL(clicked()), SLOT(lastKey()));
}

void Search::firstKey()
{
    int key;

    if (ui.radioCod->isChecked())
        key = 1;
    else if (ui.radioName->isChecked())
        key = 2;
    QString str = ui.searchEdit->text();
    emit firstClick(key,str);
}

void Search::prevKey()
{
    QString str = ui.searchEdit->text();
    emit prevClick();
}

void Search::nextKey()
{
    QString str = ui.searchEdit->text();
    emit nextClick();
}

void Search::lastKey()
{
    QString str = ui.searchEdit->text();
    emit lastClick();
}

void Search::SearchFirst(int n, int flag)
{
    ui.numlabel->setText(tr("%1").arg(n));

    ui.firstButton->setEnabled(n);
    ui.nextButton->setEnabled(n);
    ui.prevButton->setEnabled(n);
    ui.lastButton->setEnabled(n);

    if (flag == 1) {
        ui.firstButton->setEnabled(false);
        ui.prevButton->setEnabled(false);
    }

    if (flag == 2) {
        ui.nextButton->setEnabled(false);
        ui.lastButton->setEnabled(false);
    }
}
