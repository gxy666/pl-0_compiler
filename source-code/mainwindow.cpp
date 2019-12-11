#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->pushButton_2->setEnabled(false);
    g = new Grammer();
    exer = new Exer();
    input_buff = new QVector<int>();
    this->setFocusPolicy(Qt::ClickFocus);
    connect(this,SIGNAL(ready()),this,SLOT(start()));
    connect(this,SIGNAL(finish()),this,SLOT(display()));
    connect(this,SIGNAL(error()),this,SLOT(deal_error()));
    connect(exer,SIGNAL(exererror(QString)),this,SLOT(deal_exer_error(QString)));
    connect(g,SIGNAL(grammererror(QString)),this,SLOT(deal_grammer_error(QString)));
    connect(exer,SIGNAL(write_data(int)),this,SLOT(write_data(int)));
    connect(exer,SIGNAL(finish()),this,SLOT(exe_finish()));
    connect(exer,SIGNAL(new_read_data(int)),this,SLOT(add_read(int)));
    word_check_list.append(new Word("+",PLUS,0));
    word_check_list.append(new Word("-",SUB,0));
    word_check_list.append(new Word("*",STAR,0));
    word_check_list.append(new Word("/",DIVIDE,0));
    word_check_list.append(new Word(":=",FUZHI,0));
    word_check_list.append(new Word("=",EQUAL,0));
    word_check_list.append(new Word("#",JING,0));
    word_check_list.append(new Word("<",LESS,0));
    word_check_list.append(new Word("<=",LESSEQUAL,0));
    word_check_list.append(new Word(">",LARGER,0));
    word_check_list.append(new Word(">=",LARGEREQUAL,0));
    word_check_list.append(new Word("const",CON,0));
    word_check_list.append(new Word("procedure",PRO,0));
    word_check_list.append(new Word("begin",BEGIN,0));
    word_check_list.append(new Word("end",END,0));
    word_check_list.append(new Word("odd",ODD,0));
    word_check_list.append(new Word("if",IF,0));
    word_check_list.append(new Word("then",THEN,0));
    word_check_list.append(new Word("while",WHILE,0));
    word_check_list.append(new Word("var",VA,0));
    word_check_list.append(new Word("call",CALL,0));
    word_check_list.append(new Word("read",READ,0));
    word_check_list.append(new Word("write",WRITE,0));
    word_check_list.append(new Word("do",DO,0));
    word_check_list.append(new Word("(",ZUOKUOH,0));
    word_check_list.append(new Word(")",YOUKUOH,0));
    word_check_list.append(new Word(";",FENHAO,0));
    word_check_list.append(new Word(",",DOUHAO,0));
    display_list = new QVector<Word*>();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QChar MainWindow::get_char()
{
    if(all_word.length()!=0)
    {
        QChar temp = all_word.at(0);
        all_word = all_word.right(all_word.length()-1);
        return temp;
    }
    else {
        QChar temp(' ');
        return temp;
    }
}

void MainWindow::keyPressEvent(QKeyEvent *ev)
{
    if(ev->key() == Qt::Key_Return)
    {
       on_pushButton_3_clicked();
       return;
    }
}

void MainWindow::exe_finish()
{
    QMessageBox::information(this, tr("Congratulation"), tr("程序执行完毕"));
}

void MainWindow::deal_error()
{
    display_list->clear();
    ui->textEdit_2->clear();
    ui->textEdit_3->clear();
    ui->textEdit_4->clear();
    if(!word_error)
    {
        QMessageBox::information(this, tr("Error"), tr("你输入的代码词法有误"));
        word_error = true;
    }
}

void MainWindow::deal_grammer_error(QString a)
{
    if(!grammer_error&&!word_error)
    {
        grammer_error = true;
        QMessageBox::information(this, tr("Error"), tr("你输入的代码语法有误，")+a);
    }
}

void MainWindow::deal_exer_error(QString a)
{
    if(!grammer_error&&!word_error&&!exer_error)
    {
        exer_error = true;
        ui->textEdit_6->clear();
        QMessageBox::information(this, tr("Error"), tr("你输入的代码执行有误，")+a);
    }
}

void MainWindow::write_data(int a)
{
    ui->textEdit_6->append(QString::number(a));
}

void MainWindow::retract(QChar a)
{
    all_word = a+all_word;
}

void MainWindow::get_bc()
{
    while (all_word.length()>0&&all_word.at(0).isSpace()) {
        all_word = all_word.right(all_word.length()-1);
    }
}

void MainWindow::start()
{
    while(all_word.length()>0)
    {
        this->getSym();
    }
    emit finish();
}

int MainWindow::reserve(QString a)
{
    for(int i = 0;i<word_check_list.length();++i)
    {
        if(a.compare(word_check_list.at(i)->value)==0)
        {
            return word_check_list.at(i)->type;
        }
    }
    return CHA;
}

void MainWindow::getSym()
{
    int code = 0;
    int value = 0;
    this->get_bc();
    QString current_string;
    QChar current_char = this->get_char();
    if(current_char.isLetter())
    {
        while(current_char.isLetter()||current_char.isDigit())
        {
            current_string += current_char;
            current_char = this->get_char();
        }
        this->retract(current_char);
        code = this->reserve(current_string);
        if(code==CHA)
        {
            Word *temp = new Word(current_string,code,value);//识别到一个标识符
            display_list->append(temp);
        }
        else
        {
            Word *temp = new Word(current_string,code,value);
            display_list->append(temp);//识别到一个保留字
        }
    }
    else if(current_char.isDigit())
    {
        while (current_char.isDigit())
        {
            current_string+=current_char;
            current_char = this->get_char();
        }
        this->retract(current_char);
        Word *temp = new Word(current_string,INT,value);//识别到一个常量
        display_list->append(temp);
    }
    else if(current_char==':')
    {
        QChar temp_char = this->get_char();
        if (temp_char=='=')
        {
            current_string+=current_char;
            current_string+=temp_char;
            Word *temp = new Word(current_string,FUZHI,value);
            display_list->append(temp);
        }
        else
        {
            emit error();
        }
    }
    else if(current_char=='>'||current_char=='<')
    {
        QChar temp_char = this->get_char();
        if(temp_char=='=')
        {
            current_string+=current_char;
            current_string+=temp_char;
            code = this->reserve(current_string);
            Word *temp = new Word(current_string,code,value);
            display_list->append(temp);//识别到一个保留字
        }
        else
        {
            this->retract(temp_char);
            current_string+=current_char;
            code = this->reserve(current_string);
            Word *temp = new Word(current_string,code,value);
            display_list->append(temp);//识别到一个保留字
        }
    }
    else
    {
        current_string+=current_char;
        code = this->reserve(current_string);
        if(code!=CHA)
        {
            Word *temp = new Word(current_string,code,value);
            display_list->append(temp);//识别到一个保留字
        }
        else
        {
            if(current_char!=' ')
                emit error();
        }

    }
}

void MainWindow::display()
{
    if(!word_error)
    {
        for(int i = 0;i<display_list->length();++i)
        {
            ui->textEdit_3->append(display_list->at(i)->get_information());
            ui->textEdit_3->append("\r\n");
        }
        root = g->P(display_list);
    }
    if(!grammer_error&&!word_error)
    {
        //ui->pushButton_2->setEnabled(true);
        QMessageBox::information(this, tr("Congratulation"), tr("语法分析完成"));
        QVector<Identify*> *id_list = g->get_id_list();
        QVector<Order*> *order_list = g->get_code_list();
        exer->set_order(order_list);
        for(int i = 0;i<id_list->length();++i)
        {
            ui->textEdit_2->append(id_list->at(i)->get_information());
            ui->textEdit_2->append("\r\n");
        }
        for(int i = 0;i<order_list->length();++i)
        {
            ui->textEdit_4->append(QString::number(i)+" "+order_list->at(i)->get_information());
            ui->textEdit_4->append("\r\n");
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    all_word = ui->textEdit->toPlainText();
    display_list->clear();
    ui->textEdit_2->clear();
    ui->textEdit_3->clear();
    ui->textEdit_4->clear();
    ui->textEdit_5->clear();
    ui->textEdit_6->clear();
    ui->textEdit_7->clear();
    input_buff->clear();
    grammer_error = false;
    word_error = false;
    exer_error = false;
    emit ready();
}

void MainWindow::on_pushButton_2_clicked()
{
    //ui->pushButton_2->setEnabled(false);
    if(root==nullptr)
    {
        QMessageBox::information(this, tr("ERROR"), tr("您还没有提交程序"));
    }
    else
    {
        if(grammer_error)
            QMessageBox::information(this, tr("ERROR"), tr("您提交的程序语法有误"));
        else
        {
            TreeMainWindow *tr = new TreeMainWindow(root);
            tr->show();
        }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->textEdit_5->clear();
    input_buff->clear();
    QString all_int = ui->textEdit_7->toPlainText();
    QStringList int_list = all_int.split(",");
    for(int i = 0;i<int_list.length();++i)
    {
        QString s = int_list[i];
        bool test = false;
        int value = s.toInt(&test);
        if(value==-32768)
        {
            test = false;
        }
        if(test)
        {
            input_buff->append(value);
        }
        else
        {
            QMessageBox::information(this, tr("ERROR"), tr("您提交的数据有误"));
            input_buff->clear();
            return;
        }
    }
    ui->textEdit_5->clear();
    QMessageBox::information(this, tr("Congratulations"), tr("提交成功"));
}

void MainWindow::on_pushButton_4_clicked()
{
    if(root==nullptr)
    {
        QMessageBox::information(this, tr("ERROR"), tr("您还没有提交程序"));
        return;
    }
    if(word_error)
    {
        QMessageBox::information(this, tr("ERROR"), tr("您提交的程序词法有误"));
        return;
    }
    if(grammer_error)
    {
        QMessageBox::information(this, tr("ERROR"), tr("您提交的程序语法有误"));
        return;
    }
    if(input_buff->length()==0)
    {
        QMessageBox::information(this, tr("WARNING"), tr("此时您的数据为空（稍后可以在运行时输入数据）"));
    }
    exer_error = false;
    ui->textEdit_6->clear();
    for(int i = 0;i<input_buff->length();i++)
    {
        add_read(input_buff->at(i));
    }
    exer->deal(input_buff);
}

void MainWindow::add_read(int a)
{
    QString temp = ui->textEdit_5->toPlainText();
    if(temp.isEmpty())
    {
        temp+=QString::number(a);
        ui->textEdit_5->clear();
        ui->textEdit_5->append(temp);
    }
    else {
        temp+=",";
        temp+=QString::number(a);
        ui->textEdit_5->clear();
        ui->textEdit_5->append(temp);
    }
}
