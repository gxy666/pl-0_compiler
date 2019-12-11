#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "word.h"
#include <QMessageBox>
#include "grammer.h"
#include "exer.h"
#include "treemainwindow.h"
#include <QKeyEvent>
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Treenode *root = nullptr;
private slots:
    void on_pushButton_clicked();
    void start();
    void display();
    void deal_error();
    void deal_grammer_error(QString);
    void deal_exer_error(QString);
    void on_pushButton_2_clicked();
    void write_data(int);
    void on_pushButton_3_clicked();
    void add_read(int);
    void on_pushButton_4_clicked();
    void exe_finish();
protected:
    virtual void keyPressEvent(QKeyEvent *ev);

signals:
    void ready();
    void finish();
    void error();
private:
    bool grammer_error = false;
    bool word_error = false;
    bool exer_error = false;
    Ui::MainWindow *ui;
    QString all_word;
    QVector<Word*> word_check_list;
    QVector<Word*> *display_list;
    QVector<int> *input_buff;
    QChar get_char();
    void retract(QChar);
    void getSym();
    void get_bc();
    int reserve(QString);
    Grammer *g;
    Exer *exer;
};

#endif // MAINWINDOW_H
