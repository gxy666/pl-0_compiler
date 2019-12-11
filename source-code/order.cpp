#include "order.h"

Order::Order(QString n,QObject *parent) : QObject(parent)
{
    name = n;
}

QString Order::get_information()
{
    QString ans =  name;
    ans += "  ";
    ans += QString::number(l);
    ans += "  ";
    switch (a) {
    case OPR_ADD:
        ans += "ADD";
        break;
    case OPR_SUB:
        ans += "SUB";
        break;
    case OPR_MUL:
        ans += "MUL";
        break;
    case OPR_DIV:
        ans += "DIV";
        break;
    case OPR_FU:
        ans += "FU";
        break;
    case OPR_LAR:
        ans += "LAR";
        break;
    case OPR_LARE:
        ans += "LARE";
        break;
    case OPR_LES:
        ans += "LES";
        break;
    case OPR_LESE:
        ans += "LESE";
        break;
    case OPR_EQU:
        ans += "EQU";
        break;
    case OPR_NEQU:
        ans += "NEQU";
        break;
    case OPR_READ:
        ans += "READ";
        break;
    case OPR_WRI:
        ans += "WRI";
        break;
    default:
        ans += QString::number(a);
        break;
    }
    ans += ";";
    return ans;
}
