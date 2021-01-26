#ifndef EDITTICKET_H
#define EDITTICKET_H

#include "ui_editticket.h"

class EditTicket : public QDialog, private Ui::EditTicket
{
    Q_OBJECT

public:
    explicit EditTicket(QWidget *parent = 0);
    QString Title() { return lineEdit->text(); }
    QString Descr() { return textEdit->toPlainText(); }
};

#endif // EDITTICKET_H
