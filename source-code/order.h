#ifndef ORDER_H
#define ORDER_H

#include <QObject>
#include <QString>


#define OPR_ADD 200
#define OPR_SUB 201
#define OPR_MUL 202
#define OPR_DIV 203
#define OPR_FU 204
#define OPR_LAR 205
#define OPR_LARE 206
#define OPR_LES 207
#define OPR_LESE 208
#define OPR_EQU 209
#define OPR_NEQU 210
#define OPR_READ 211
#define OPR_WRI 212


class Order : public QObject
{
    Q_OBJECT
public:
    explicit Order(QString n,QObject *parent = nullptr);
    QString name;
    int l=0;
    int a=0;
    QString get_information();
signals:

public slots:
};

#endif // ORDER_H
