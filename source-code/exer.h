#ifndef EXER_H
#define EXER_H

#include <QObject>
#include <QVector>
#include "order.h"
#include "inputdialog.h"
#define MAX_STACK_LENTH 1600
class Exer : public QObject
{
    Q_OBJECT
public:
    explicit Exer(QObject *parent = nullptr);
    void deal(QVector<int> *);
    void set_order(QVector<Order*>*a);
signals:
    void exererror(QString);
    void write_data(int);
    void new_read_data(int);
    void finish();
public slots:
    void add_input(int);
private:
    int stack_pop();
    void ret(int a);
    int read_data();
    void stack_push(int);
    int sp = 0;
    int current_order = 0;
    int pc = 0;
    int input_index = 0;
    int stack_top = 0;
    bool error_flag = false;
    QVector<int> *stack;
    QVector<Order*> *order_list;
    QVector<int> *input_buff;
};

#endif // EXER_H
