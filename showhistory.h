#ifndef SHOWHISTORY_H
#define SHOWHISTORY_H

#include <QObject>
#include <qprinter.h>
#include <QFileDialog>
#include "ui_showhistory.h"

class showHistory : public QDialog
{
    Q_OBJECT

public:
    explicit showHistory(QWidget *parent = 0);
    void setText(QString);

private:
    Ui::showHistory ui;

private slots:
    void saveas();
};

#endif // SHOWHISTORY_H
