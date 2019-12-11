#ifndef GRAMMER_H
#define GRAMMER_H

#include <QObject>
#include "word.h"
#include <QVector>
#include "treenode.h"
#include "order.h"
#include "identify.h"
#include "id_table.h"

class Grammer : public QObject
{
    Q_OBJECT
public:
    explicit Grammer(QObject *parent = nullptr);
    Treenode* P(QVector<Word*> *d);
    QVector<Identify*> *get_id_list();
    QVector<Order*> *get_code_list();
signals:
    void grammererror(QString);
public slots:

private:
    QVector<Order*> *code_list;//
    //QVector<Identify*> *id_list;//
    Id_Table *root_table;//
    Id_Table *current_table;//
    QVector<Word*> *display;
    int max;
    int current_level;
    int id_list_address;
    int current_word_index;
    Treenode *root;
    Treenode *current_node;
    bool end = false;
    bool error = false;
    void gen_order(QString ,int ,int);
    int  getword();
    void advance();
    void FP();
    void CI();
    void CD();
    void VI();
    void S();
    void GIVE();
    void FH();
    void HEAD();
    void PI();
    void CON_G();
    void X();
    void AS();
    void MD();
    void SON();
    void CONS();
    void COND();
    void EQ();
    void REL();
    void CHA_G();
    void NUM();
    void R();
    void W();
    void WH();

};

#endif // GRAMMER_H
