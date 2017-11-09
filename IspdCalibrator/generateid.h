#ifndef GENERATEID_H
#define GENERATEID_H

#include <QDialog>
#include <QSerialPort>
#include <QTimer>
#include <QSettings>
#include <QDir>
#include <QTextCodec>

namespace Ui {
class GenerateID;
}

class GenerateID : public QDialog
{
    Q_OBJECT

public:
    explicit GenerateID(QWidget *parent = 0);
    ~GenerateID();
    void timerEvent(QTimerEvent *ev);

protected:
    void closeEvent(QCloseEvent * event) override;

signals:
    void quit();
    void goto_checkISPD();

private slots:
    void start();
    void on_pushButton_confirm_hz_clicked();
    void on_pushButton_customize_clicked();
    void on_pushButton_applicate_clicked();
    void on_pushButton_record_clicked();
    void on_pushButton_open_sp_clicked();
    void onRead();
    void onUsername(const QString & username);
    void on_comboBox_hz_currentIndexChanged(const QString &arg1);
    void on_pushButton_test_ispd_clicked();

    void on_lineEdit_ispd_id_editingFinished();

    void on_comboBox_hz_currentIndexChanged(int index);

    void on_comboBox_hz_activated(const QString &arg1);

private:
    Ui::GenerateID *ui;
    //qint32 m_current_sign_id;
    std::string m_current_sign_id;
    qint32 m_user_id;
    qint32 m_ispd_id;
    QString m_username;

    QSerialPort m_spt;
    bool m_status_open;

    bool m_is_write_id;
    bool m_is_write_hz;

    //超时处理
    int m_timeout;
};

#endif // GENERATEID_H
