#ifndef ID_TABLE_H
#define ID_TABLE_H

#include <QObject>
#include <QVector>
#include "identify.h"
class Id_Table : public QObject
{
    Q_OBJECT
public:
    explicit Id_Table(Id_Table* p = nullptr,QObject *parent = nullptr);
    QVector<Identify*> *id_list;
    QVector<Id_Table*> *table_list;
    bool append_id(Identify*);
    void append_table(Id_Table*);
    QVector<Identify*> *get_display_id_list();
    Id_Table *par;
    QString table_name;
    int addr = 3;
    bool get_var_id(int *l,int *a,QString n,int current_level);
    bool get_con_id(int *a,QString n,int current_level);
    int get_id_num();
    bool set_pro_entrance(QString,int);
    bool get_pro_entrance(int *l,int *a,QString name,int current_level);
signals:

public slots:
};

#endif // ID_TABLE_H
