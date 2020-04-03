#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_btnOK_clicked()
{
    user=ui->editUser->text().trimmed();
    password=ui->editPassword->text().trimmed();
    if(user.isEmpty()||password.isEmpty())
    {
        QMessageBox::critical(this,"错误","用户名和密码不能为空");
        if(user.isEmpty())
        {
            ui->editUser->setFocus();
            ui->editPassword->clear();
        }
        else
        {
            ui->editPassword->setFocus();
        }
    }
    else
    {
        emit accept();
    }
}
