#ifndef EXPORTDATA_H
#define EXPORTDATA_H

#include <QObject>
#include <QDebug>
#include <QDialog>
#include <QAbstractTableModel>
#include <QLayout>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QLineEdit>

class ExportData : public QObject
{
    Q_OBJECT

private:
    QDialog *ui;
    QAbstractTableModel *model;
    QDialog *init_dialog(QStringList);
    QCheckBox *create_checkbox(QString name);

public:
    explicit ExportData(QAbstractTableModel *mdl, QObject *parent = 0);
    ~ExportData();
    void exportToCSV();

signals:

public slots:
};

#endif // EXPORTDATA_H
