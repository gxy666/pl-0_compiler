#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>
#include <QMessageBox>
namespace Ui {
class InputDialog;
}

class InputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InputDialog(QWidget *parent = 0);
    ~InputDialog();

private slots:
    void on_pushButton_clicked();
signals:
    void submit_num(int);

private:
    Ui::InputDialog *ui;
};

#endif // INPUTDIALOG_H
