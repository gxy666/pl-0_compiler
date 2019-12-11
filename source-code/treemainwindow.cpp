#include "treemainwindow.h"
#include "ui_treemainwindow.h"

TreeMainWindow::TreeMainWindow(Treenode *a,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TreeMainWindow)
{
    ui->setupUi(this);
    this->setFixedHeight(1000);
    this->setFixedWidth(1900);
    QScrollArea *s = new QScrollArea(this);
    s->setGeometry(0, 0, 1900, 1000);
    TreeWindow *w = new TreeWindow(a,s);
    s->setWidget(w);
}

TreeMainWindow::~TreeMainWindow()
{
    delete ui;
}
