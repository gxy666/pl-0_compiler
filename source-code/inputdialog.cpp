#include "inputdialog.h"
#include "ui_inputdialog.h"

InputDialog::InputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputDialog)
{
    ui->setupUi(this);
    QRegExp regx("[0-9]+$");
    QValidator* validator = new QRegExpValidator(regx, ui->lineEdit);
    ui->lineEdit->setValidator(validator);
}

InputDialog::~InputDialog()
{
    delete ui;
}

void InputDialog::on_pushButton_clicked()
{
    bool test = false;
    int ans = ui->lineEdit->text().toInt(&test);
    if(ans==-32768)
    {
        test = false;
    }
    if(test)
    {
        emit submit_num(ans);
        QMessageBox::information(this, tr("Correct"), tr("提交成功"));
        this->close();
    }
    else
    {
        QMessageBox::information(this, tr("Error"), tr("你输入的有误"));
    }
}
