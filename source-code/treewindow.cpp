#include "treewindow.h"
#include "ui_treewindow.h"

TreeWindow::TreeWindow(Treenode* r,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TreeWindow)
{
    ui->setupUi(this);
    root = r;
    this->setGeometry(0, 0, 9900, 6800);
    queue = new QQueue<Treenode*>();
    this->deal();
}

TreeWindow::~TreeWindow()
{
    delete ui;
}

void TreeWindow::deal()
{
    int level = 0;
    int level_count = 0;
    queue->enqueue(root);
    while (!queue->isEmpty())
    {
        Treenode *current_node = queue->dequeue();
        if(current_node->y==level+1)
        {
            level++;
            level_count = 0;
        }
        for(int i = 0;i<current_node->children->length();++i)
        {
            queue->enqueue(current_node->children->at(i));
        }
        current_node->x = level_count;
        QLabel* label = new QLabel(this);
        label->setText(current_node->name);
        label->setFrameShape (QFrame::Box);
        QFont font("Microsoft YaHei",13);
        label->setFont(font);
        label->setStyleSheet("border-width: 2px;border-style: solid;");
        label->setFixedHeight(40);
        label->setFixedWidth(100);
        label->setGeometry(current_node->x*110,current_node->y*200,100,40);
        label->setAlignment(Qt::AlignCenter);
        level_count++;
    }
}

void TreeWindow::paintEvent(QPaintEvent *event)
{
    queue->enqueue(root);
    while (!queue->isEmpty())
    {
        Treenode *current_node = queue->dequeue();
        for(int i = 0;i<current_node->children->length();++i)
        {
            queue->enqueue(current_node->children->at(i));
        }
        if(current_node->parent!=nullptr)
        {
            QPainter painter(this);
            painter.setPen(QPen(Qt::black,2));
            painter.drawLine(current_node->x*110+50,current_node->y*200,current_node->parent->x*110+50,current_node->parent->y*200+40);
        }
    }
}





