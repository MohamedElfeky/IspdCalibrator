#ifndef CHECKISPD_H
#define CHECKISPD_H

#include "../hdtasparser/hdtasparser/hdtasparser.h"
#include "../hdtasparser/hdtasparser/utility.h"

#include <QDialog>
#include <QCloseEvent>
#include <QSerialPort>
#include <QHash>
#include <QStandardItemModel>

#include "worker.h"
#include "tcp_worker.h"
#include "udp_worker.h"

#define  TIMEOUT				(5)

class QThread;

#define MESSAGE_RED "<font size = 200 color = red ><strong>"
#define MESSAGE_GREEN "<font size = 200 color = blue ><strong>"
#define MESSAGE_END "</strong></font>"

namespace Ui {
class CheckIspd;
}

class CheckIspd : public QDialog
{
    Q_OBJECT

public:
    explicit CheckIspd(QWidget *parent = 0);
    ~CheckIspd();

protected:
    void closeEvent(QCloseEvent * event) override;
signals:
    void quit();
    void goto_genID();

public slots:
    void start();
    void onSerialPortRead();
    void onUdpMessage(const QString & msg);
    void onTcpMessage(const QString & msg);
    void onMrUdpMessage(const QByteArray &msg); //add by guosj
    void onUdpLogMessage(QString log_str);      //add by guosj
    void onUdpDefaultMsg(QString def_log_str);
    void onUdpData(QString udp_data);
    bool mr_restart(const QString & ip);

private slots:
    void on_pushButton_open_sp_clicked();
    void on_pushButton_customize_clicked();
    void on_pushButton_applicate_clicked();
    void on_pushButton_ispd_cmp_clicked();
    void on_pushButton_ispd_sensor_clicked();
    void on_pushButton_ispd_no_clicked();
    void on_pushButton_ispd_version_clicked();
    void on_pushButton_ispd_hz_clicked();
    void on_pushButton_clicked();
    void on_pushButton_ispd_hr_clicked();
    void on_pushButton_readAll_clicked();

    void on_comboBox_sp_activated(const QString &arg1);

    void on_pushButton_init_clicked();

    void on_textEdit_log_windowIconTextChanged(const QString &iconText);

private:
    Ui::CheckIspd *ui;

    QSerialPort     m_spt;
    bool            m_status_open;
    QHash<uint32_t, QString> m_id_ip_map;
    QString m_err_info;
    //QStandardItemModel* m_model_list_ptr;

    QThread                 * m_udp_thread_ptr;
    serialport_udp_worker   * m_udp_worker_ptr;
    mr_udp_worker           * mmr_udp_worker_ptr;
    quint32 ipsd_id_mem;


    tcp_worker  * m_tcp_worker_ptr;
};

#endif // CHECKISPD_H
