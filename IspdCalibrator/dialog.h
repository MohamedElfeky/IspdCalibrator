#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMap>

class QAbstractButton;

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    void getWindowTittle(const QString & title);

signals:
    void send(const char * data, qint16 len);

private slots:
    void on_spinBox_valueChanged(int arg1);
    void on_buttonBox_clicked(QAbstractButton *button);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui;
    QMap<const unsigned char *, size_t> map;
    QString m_windownTitle;
};

#endif // DIALOG_H
