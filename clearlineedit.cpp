#include "clearlineedit.h"

ClearLineEdit::ClearLineEdit(QWidget *parent) :
    QLineEdit(parent)
{
    button=new QToolButton(this);
    button->setCursor(Qt::ArrowCursor);
    button->hide();
    button->setFocusPolicy(Qt::NoFocus);
    button->setIcon(QIcon::fromTheme("edit-clear"));
    button->setStyleSheet("border: none;");
    connect(this,SIGNAL(textChanged(QString)),this,SLOT(textChanged(QString)));
    connect(button,SIGNAL(clicked()),this,SLOT(clear()));

    QVBoxLayout *layout=new QVBoxLayout(this);
    layout->addWidget(button,0,Qt::AlignRight);
    layout->setSpacing(0);
    layout->setMargin(0);
}

void ClearLineEdit::textChanged(QString text)
{
    if (text.isEmpty()) button->hide();
        else button->show();
}

