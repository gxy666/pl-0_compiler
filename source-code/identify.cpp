#include "identify.h"

Identify::Identify(QObject *parent) : QObject(parent)
{

}

QString Identify::get_information()
{
    QString temp = "name:";
    temp+=this->name;
    temp+="\r\n";
    switch (type) {
    case CONST_ID:
        temp+="type:CONST";
        temp+="\r\n";
        temp+="value:";
        temp+=QString::number(this->value,10);
        temp+="\r\n";
        break;
    case VAR_ID:
        temp+="type:VAR";
        temp+="\r\n";
        break;
    case PRO_ID:
        temp+="type:PROCEDURE";
        temp+="\r\n";
        break;
    default:
        break;
    }
    temp+="level:";
    temp+=QString::number(this->level,10);
    temp+="\r\n";
    temp+="address:";
    temp+=QString::number(this->address,10);
    return temp;
}
