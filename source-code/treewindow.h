#ifndef TREEWINDOW_H
#define TREEWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QQueue>
#include <QLabel>
#include <QFont>
#include <QPainter>
#include <QPen>
#include "treenode.h"

namespace Ui {
class TreeWindow;
}

class TreeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TreeWindow(Treenode *,QWidget *parent = 0);
    ~TreeWindow();

private:
    void paintEvent(QPaintEvent *event);
    Ui::TreeWindow *ui;
    Treenode *root;
    QQueue<Treenode *> *queue;
    void deal();
};

#endif // TREEWINDOW_H
