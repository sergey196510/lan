#ifndef LCOMBOBOX_H
#define LCOMBOBOX_H

#include <QComboBox>
#include <QtSql>

class LComboBox : public QComboBox
{
    Q_OBJECT
private:
    int type;

public:
    explicit LComboBox(QWidget *parent = 0);
    void setValue(QVariant val);
    QVariant Value();
    int Type() { return type; }
    void read_data(int type);

signals:
    void Updated();

public slots:
    void reload_data();
};

#endif // LCOMBOBOX_H
