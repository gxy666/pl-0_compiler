#ifndef TREENODE_H
#define TREENODE_H
#include <QString>
#include <QVector>

class Treenode
{
public:
    QVector<Treenode*> *children;
    QString name;
    Treenode* parent;
    Treenode(QString n,Treenode *p = nullptr);
    int x = 0;
    int y = 0;
    void delete_itself();
};

#endif // TREENODE_H
