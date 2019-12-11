#ifndef WORD_H
#define WORD_H
#include <QString>

#define INT 1//数字
#define PLUS 2//+
#define SUB 3//-
#define STAR 4//*
#define DIVIDE 5///
#define FUZHI 6//:=
#define EQUAL 7//=
#define JING 8//#
#define LESS 9//<
#define LESSEQUAL 10//<=
#define LARGER 11//>
#define LARGEREQUAL 12//>=
#define CON 13//const
#define PRO 14//procedure
#define BEGIN 15//begin
#define END 16//end
#define ODD 17//odd
#define IF 18//if
#define THEN 19//then
#define WHILE 20//while
#define VA 21//VAR
#define CALL 22//call
#define READ 23//read
#define WRITE 24//write
#define DO 25//do
#define CHA 26//标识符
#define ZUOKUOH 27//(
#define YOUKUOH 28//)
#define FENHAO 29//;
#define DOUHAO 30//,
#define NUL 31//空


class Word
{
public:
    Word(QString v,int t,int p);
    QString value;
    int type;//作废，懒得删
    int position;
    QString get_information();
};

#endif // WORD_H
