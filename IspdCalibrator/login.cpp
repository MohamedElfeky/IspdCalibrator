#include "login.h"
#include "ui_login.h"
#include "common.h"

#include <QtSql>
#include <QMessageBox>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::close()
{
    this->reject();
}

void login::on_pushButton_ok_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../database/IspdCalibrator.db");
    if (!db.open()) {
        QMessageBox::critical(0, qApp->tr("数据库打开失败"),
                              qApp->tr("请检查数据库文件存放位置，"),
                              QMessageBox::Cancel);
        qCritical() << db.lastError().text();
        db.close();
        return ;
    }

    QString username = ui->lineEdit_username->text();
    if (username.isEmpty()) {
        qWarning() << "username is empty";

        QMessageBox msgBox(QMessageBox::Warning, tr("警告"), tr("用户名为空！"));
        msgBox.setStandardButtons(QMessageBox::Cancel);
        msgBox.setButtonText(QMessageBox::Cancel, tr("退出"));
        if (msgBox.exec()== QMessageBox::Cancel) {
            this->reject();
            db.close();
            return ;
        }
    }

    QString password = ui->lineEdit_password->text();
    QString command = "select user_password from USER where user_name is \'" + username + "\'";

    QSqlQuery query;
    if (!query.exec(command)) qCritical() << query.lastError();

    if (query.next()) {
        if (password != query.value(0).toString()) {
            QMessageBox msgBox(QMessageBox::Warning, tr("登录失败"),tr("用户名或密码有误！"));
            msgBox.setStandardButtons(QMessageBox::Abort);
            msgBox.setButtonText(QMessageBox::Abort, tr("退出"));
            if (msgBox.exec() == QMessageBox::Abort) {
                this->reject();
                db.close();
            }
        } else {
            this->accept();
        }
    } else {
        QMessageBox msgBox(QMessageBox::Warning, tr("登录失败"),tr("用户不存在"));
        msgBox.setStandardButtons(QMessageBox::Abort);
        msgBox.setButtonText(QMessageBox::Abort, tr("退出"));
        if (msgBox.exec() == QMessageBox::Abort) {
            this->reject();
            db.close();
            return ;
        }
    }

    emit tellUsername(username);

    db.close();

    qInfo() << "log in successfully";
}

void login::on_pushButton_cancel_clicked()
{
   this->reject();
}
