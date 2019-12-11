#include "word.h"

Word::Word(QString v,int t,int p)
{
    value = v;
    type = t;
    position = p;
}

QString Word::get_information()
{
    QString temp = "value:";
    temp+=this->value;
    temp+="\r\n";
    temp+="type:";
    temp+=QString::number(this->type,10);
    temp+="\r\n";
    temp+="position:";
    temp+=QString::number(this->position,10);
    return temp;
}
