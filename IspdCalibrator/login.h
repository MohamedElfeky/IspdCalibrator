#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();

signals:
    void tellUsername(const QString & username);

private slots:
    void close();

    void on_pushButton_ok_clicked();
    void on_pushButton_cancel_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
