#include "lan.h"
#include "ui_lan.h"

Lan::Lan(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Lan)
{
    ui->setupUi(this);

    readsettings();

    connect(ui->actionAbout_QT, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(ui->actionQuit, SIGNAL(triggered()),
            this, SLOT(close()));

    if (dbopen() == false) {
        return;
    }

    connect(ui->actionImport, SIGNAL(triggered()),
            this, SLOT(import_data()));

    items = new ListItems(this);
    setCentralWidget(items);

    QAction *mov = new QAction(tr("Movements"), this);
    connect(mov, SIGNAL(triggered()), SLOT(movements()));

    QAction *mov2 = new QAction(tr("Movements new"), this);
    connect(mov2, SIGNAL(triggered()), SLOT(movements2()));

    ui->mainToolBar->addAction(ui->actionInsert);
    ui->mainToolBar->addAction(ui->actionUpdate);
    ui->mainToolBar->addAction(ui->actionDelete);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(mov);
    ui->mainToolBar->addAction(mov2);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actionExport);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addAction(ui->actionQuit);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addActions(items->acts);

    connect(ui->actionInsert, SIGNAL(triggered()), items, SLOT(new_record()));
    connect(ui->actionExport, SIGNAL(triggered(bool)), items, SLOT(export_data()));
    connect(ui->actionAttributes, SIGNAL(triggered(bool)), SLOT(listAttributes()));

    setWindowTitle(tr("Local Area Network"));
}

Lan::~Lan()
{
    writesettings();
    delete ui;
}

bool Lan::dbopen()
{
    QSqlDatabase db;
    bool createdb = false;

    if(!QFile("lan.db").exists())
        createdb = true;

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("lan.db");
    if (!db.open()) {
        QMessageBox::critical(this, tr("Open database"), tr("Error in open database file"));
        return false;
    }

    if (createdb == true) {
        QSqlQuery q;

        q.exec("CREATE TABLE attr_descr(id integer primary key autoincrement, type int, name text, active int default 0, bd date, descr text, flag int default 0)");
        q.exec("CREATE TABLE attr_link(id integer primary key autoincrement, i_id int, a_id int, type int, bd date, ld date, active int default 0, descr text, d_id int default 0, open datetime, close datetime)");
        q.exec("CREATE TABLE item(id integer primary key autoincrement, cod text unique, name text, note text)");
        q.exec("CREATE TABLE document(id integer primary key autoincrement, data blob)");
        q.exec("CREATE TABLE tickets(id integer primary key autoincrement, i_id int, tm timestamp, title text, message text)");
        q.exec("CREATE TABLE item_moves(i_id int, t_id int, prev int, next int, dt date)");
    }

    return true;
}

void Lan::import_data()
{

}

void Lan::readsettings()
{
    QSettings settings("AIST", "Lan");

    restoreGeometry(settings.value("/geometry").toByteArray());
}

void Lan::writesettings()
{
    QSettings settings("AIST", "Lan");

    settings.setValue("/geometry", saveGeometry());
}

void Lan::movements()
{
    ListMovements lm(new ListMovements1Model);

    lm.exec();
}

void Lan::movements2()
{
    ListMovements lm(new ListMovements2Model);
    lm.exec();
}

void Lan::listAttributes()
{
    listAttribute *la = new listAttribute(this);

    connect(la, SIGNAL(changeAttribute(int)), items, SLOT(update_attr(int)));

    la->exec();
}
