#ifndef TREEMAINWINDOW_H
#define TREEMAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include "treewindow.h"

namespace Ui {
class TreeMainWindow;
}

class TreeMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TreeMainWindow(Treenode* ,QWidget *parent = 0);
    ~TreeMainWindow();

private:
    Ui::TreeMainWindow *ui;
};

#endif // TREEMAINWINDOW_H
