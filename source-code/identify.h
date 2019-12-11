#ifndef IDENTIFY_H
#define IDENTIFY_H

#define CONST_ID 100
#define PRO_ID 101
#define VAR_ID 102


#include <QObject>
#include <QString>
#include "word.h"
class Identify : public QObject
{
    Q_OBJECT
public:
    explicit Identify(QObject *parent = nullptr);
    QString name;
    int type;
    int value;
    int level;
    int address;
    QString get_information();
public slots:
};

#endif // IDENTIFY_H
