#ifndef SEARCH_H
#define SEARCH_H

#include "ui_search.h"

class Search : public QDialog
{
    Q_OBJECT

public:
    explicit Search(QWidget *parent = 0);

private:
    Ui::Search ui;

private slots:
    void firstKey();
    void prevKey();
    void nextKey();
    void lastKey();

public slots:
    void SearchFirst(int,int);

signals:
    void firstClick(int,QString);
    void prevClick();
    void nextClick();
    void lastClick();
};

#endif // SEARCH_H
