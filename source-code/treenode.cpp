#include "treenode.h"

Treenode::Treenode(QString n,Treenode *p)
{
    name = n;
    children = new QVector<Treenode*>();
    parent = p;
    if(parent!=nullptr)
    {
        parent->children->append(this);
        y = parent->y+1;
    }
}

void Treenode::delete_itself()
{
    parent->children->pop_back();
}

