#include "id_table.h"

Id_Table::Id_Table(Id_Table* p,QObject *parent) : QObject(parent)
{
    id_list = new QVector<Identify*>();
    table_list = new QVector<Id_Table*>();
    par = p;
}

bool Id_Table::append_id(Identify* t)
{
    for(int i = 0;i<id_list->length();i++)
    {
        if(t->name==id_list->at(i)->name)
            return false;
    }
    id_list->append(t);
    return true;
}

void Id_Table::append_table(Id_Table *t)
{
    table_list->append(t);
}

QVector<Identify*> *Id_Table::get_display_id_list()
{
    QVector<Identify*> *ans = new QVector<Identify*>(*id_list);
    for(int i = 0;i<table_list->length();i++)
    {
        ans->append(*(table_list->at(i)->get_display_id_list()));
    }
    return ans;
}

bool Id_Table::get_pro_entrance(int *l,int *a,QString n,int current_level)
{
    for(int i = 0;i<id_list->length();i++)
    {
        if(id_list->at(i)->type==PRO_ID)
        {
            if(id_list->at(i)->name==n)
            {
                *l = current_level-id_list->at(i)->level;
                *a = id_list->at(i)->value;
                return true;
            }
        }
    }
    if(par==nullptr)
    {
        return false;
    }
    else
    {
        return par->get_pro_entrance(l,a,n,current_level);
    }
}

bool Id_Table::set_pro_entrance(QString n, int add)
{
    for(int i = 0;i<id_list->length();i++)
    {
        if(id_list->at(i)->type==PRO_ID)
        {
            if(id_list->at(i)->name==n)
            {
                id_list->at(i)->value = add;
                return true;
            }
        }
    }
    return false;
}

bool Id_Table::get_var_id(int *l, int *a, QString n,int current_level)
{
    for(int i = 0;i<id_list->length();i++)
    {
        if(id_list->at(i)->type==VAR_ID)
        {
            if(id_list->at(i)->name==n)
            {
                *l = current_level-id_list->at(i)->level;
                *a = id_list->at(i)->address;
                return true;
            }
        }
    }
    if(par==nullptr)
    {
        return false;
    }
    else
    {
        return par->get_var_id(l,a,n,current_level);
    }
}

bool Id_Table::get_con_id(int *a, QString n,int current_level)
{
    for(int i = 0;i<id_list->length();i++)
    {
        if(id_list->at(i)->type==CONST_ID)
        {
            if(id_list->at(i)->name==n)
            {
                *a = id_list->at(i)->value;
                return true;
            }
        }
    }
    if(par==nullptr)
    {
        return false;
    }
    else
    {
        return par->get_con_id(a,n,current_level);
    }
}

int Id_Table::get_id_num()
{
    int ans=0;
    for(int i = 0;i<id_list->length();i++)
    {
        if(id_list->at(i)->type==VAR_ID)
            ans++;
    }
    return ans;
}
