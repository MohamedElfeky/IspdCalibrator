#include "../hdtasparser/hdtasparser/hdtasparser.h"
#include "../hdtasparser/hdtasparser/utility.h"

#include "checkispd.h"
#include "ui_checkispd.h"
#include "common.h"
#include "udp_worker.h"
#include "pubdata.h"

#include <QSerialPortInfo>
#include <QDebug>
#include <QThread>
#include <QNetworkInterface>
#include <QTime>
#include <QMessageBox>

CheckIspd::CheckIspd(QWidget *parent) :
    m_status_open(false),
    QDialog(parent),
    ui(new Ui::CheckIspd)
{
    ui->setupUi(this);

    ui->pushButton_applicate->setDisabled(true);   //结束配置按钮
    ui->pushButton_customize->setDisabled(true);   //开始配置按钮
    ui->pushButton_ispd_no->setDisabled(true);     //标签号按钮
    ui->pushButton_readAll->setDisabled(true);     //一键读取按钮
    ui->pushButton_ispd_version->setDisabled(true);//获取版本号按钮
    ui->pushButton_ispd_hz->setDisabled(true);     //采样率按钮
    ui->pushButton_ispd_hr->setDisabled(true);     //心率按钮
    ui->pushButton_ispd_sensor->setDisabled(true); //获取传感器按钮
    ui->pushButton_ispd_cmp->setDisabled(true);    //比较数据按钮

    ui->pushButton->setEnabled(false);
    this->ui->label_status->clear();
    QString local_com_ip;
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    foreach (QHostAddress address, list)
    {
       if(address.protocol() == QAbstractSocket::IPv4Protocol)
       {
           if(address.toString().contains("127.0."))
           {
               continue;
           }
           local_com_ip = address.toString();
           ui->comboBox_mmr_ip->addItem(local_com_ip);
       }
    }

    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if(serial.open(QIODevice::ReadWrite))
        {
            ui->comboBox_sp->addItem(serial.portName());
            serial.close();
        }
    }

    connect(&m_spt, SIGNAL(readyRead()), this, SLOT(onSerialPortRead()));

    //tcp
    m_tcp_worker_ptr = new tcp_worker(this);
    if (!m_tcp_worker_ptr)
    {
        qFatal("can not assign memory any more");
        return ;
    }
    connect(m_tcp_worker_ptr, SIGNAL(sendTcpMessage(QString)),
            this, SLOT(onTcpMessage(QString)));

    if (-1 == m_tcp_worker_ptr->init())
    {
        ui->label_status->setText(QString::fromLocal8Bit("TCP服务器初始化失败,请检查网络配置..."));
        qCritical() << "tcp server init failed";
        return ;
    }
    qInfo() << "tcp server started";

    mmr_udp_worker_ptr = new mr_udp_worker(this);
    if (!mmr_udp_worker_ptr)
    {
        qFatal("can not assign memory any more");
        return ;
    }

    connect(mmr_udp_worker_ptr, SIGNAL(sendUdpMessage(QByteArray)), this, SLOT(onMrUdpMessage(QByteArray)));
    if (!mmr_udp_worker_ptr->init())
    {
        ui->label_status->setText(QString::fromLocal8Bit("终端UDP服务器初始化失败,请检查网络配置..."));
        qCritical() << "mr udp server init failed";
        return ;
    }
    qInfo() << "mr udp server started";

    //udp
    m_udp_thread_ptr = new QThread(this);
    m_udp_worker_ptr = new serialport_udp_worker(0);
    if (!m_udp_thread_ptr | !m_udp_worker_ptr)
    {
        qFatal("can not assign memory any more");
        return ;
    }
    connect(m_udp_thread_ptr, SIGNAL(finished()), m_udp_thread_ptr, SLOT(deleteLater()));
    connect(m_udp_worker_ptr, SIGNAL(sendUdpMessage(QString)), this, SLOT(onUdpMessage(QString)));
    connect(m_udp_worker_ptr, SIGNAL(sendUdpLogMessage(QString)), this, SLOT(onUdpLogMessage(QString)));
    connect(m_udp_worker_ptr, SIGNAL(sendUdpDefaultMsg(QString)), this, SLOT(onUdpDefaultMsg(QString)));
    connect(m_udp_worker_ptr, SIGNAL(sendUdpData(QString)), this, SLOT(onUdpData(QString)));
    m_udp_worker_ptr->setupWorker(m_udp_thread_ptr);
    m_udp_worker_ptr->moveToThread(m_udp_thread_ptr);
    m_udp_thread_ptr->start();
    qInfo() << "upd server started";
}

CheckIspd::~CheckIspd()
{
    delete ui;
}

void CheckIspd::onMrUdpMessage(const QByteArray &msg)
{
    this->ui->label_status->clear();
    QString recv_msg(msg);
    if(recv_msg.contains(QRegExp("[<,>]")))
    {
        QStringList id_ip_list = recv_msg.split(QRegExp("[<,>]"));
        bool ok;
        uint32_t id = id_ip_list.at(1).toInt(&ok);
        if (!ok)
        {
            ui->label_status->setText(QString::fromLocal8Bit("从Map中获取ID失败..."));
            qCritical() << "fail to get id from id_ip map";
            return ;
        }

        QString ip = id_ip_list.at(2);
        if (ip.isEmpty())
        {
            ui->label_status->setText( QString::fromLocal8Bit("从Map中获取IP失败..."));
            qCritical() << "fail to get ip from id_ip map";
            return ;
        }
        m_id_ip_map.insert(id, ip);
        return ;
    }
}

void CheckIspd::onUdpData(QString udp_data)
{
    //ui->textEdit_log->append(udp_data);
}

void CheckIspd::onUdpLogMessage(QString log_str)
{
    ui->textEdit_log->append(log_str);
#if 0
    QStandardItem*      item_list_str;
    item_list_str = new QStandardItem(log_str);
    m_model_list_ptr->appendRow(item_list_str);
#endif
}

void CheckIspd::onUdpDefaultMsg(QString def_log_str)
{
    //ui->textEdit_log->append(def_log_str);
}

void CheckIspd::closeEvent(QCloseEvent *event)
{
    event->accept();

    m_udp_thread_ptr->quit();
    m_udp_thread_ptr->wait();

    m_udp_worker_ptr->deleteLater();

    emit quit();
}

void CheckIspd::start()
{
    this->showMaximized();
}

//从串口中读取所有数据的函数
void CheckIspd::onSerialPortRead()
{
    m_spt.waitForReadyRead(100);
    QByteArray buf = m_spt.readAll();
    if (buf.length() < 5) return ;
    qDebug() << "size = " << buf.size();
    qDebug() << "% recv buf = " << buf;

    serialPort::REP_TYPE type = static_cast<serialPort::REP_TYPE>(buf.at(2));
    QString errstring;
    serialPort::ResPkg<serialPort::ResResult> res(buf.data(), buf.length());
    switch (type)
    {
        case serialPort::REP_ERR:
        {
            ui->label_status->clear();
            if (serialPort::ERR_CRC == res.getData().getRes())
            {
                errstring =  QString::fromLocal8Bit("CRC出错");
                qCritical() << errstring;
                ui->label_status->setText(errstring);
            }
            else if (serialPort::ERR_FRM == res.getData().getRes())
            {
                errstring =  QString::fromLocal8Bit("帧类型出错");
                qCritical() << errstring;
                ui->label_status->setText(errstring);
            }
            else
            {
                errstring =  QString::fromLocal8Bit("不知类型错误");
                qCritical() << errstring;
                ui->label_status->setText(errstring);
            }
        } break;

        case serialPort::REP_WR_RES:
        {
            ui->label_status->clear();

            if (serialPort::RES_SUCCESS == res.getData().getRes())
            {
                errstring =  QString::fromLocal8Bit("配置成功");
                qDebug() << errstring;
                ui->label_status->setText(errstring);

                if (!ui->pushButton_customize->isEnabled())
                {
                    ui->pushButton_ispd_no->setEnabled(true);
                    ui->pushButton_readAll->setEnabled(true);
                    ui->pushButton_ispd_version->setEnabled(true);
                    ui->pushButton_ispd_hz->setEnabled(true);
                    ui->pushButton_ispd_hr->setEnabled(true);
                    ui->pushButton_ispd_sensor->setEnabled(true);
                    ui->label_status->setText( QString::fromLocal8Bit("已进入配置模式"));
                }

                if (!ui->pushButton_applicate->isEnabled())
                {
                    ui->pushButton_ispd_no->setEnabled(false);
                    ui->pushButton_readAll->setEnabled(false);
                    ui->pushButton_ispd_version->setEnabled(false);
                    ui->pushButton_ispd_hz->setEnabled(false);
                    ui->pushButton_ispd_hr->setEnabled(false);
                    ui->pushButton_ispd_sensor->setEnabled(false);
                    ui->pushButton_ispd_cmp->setEnabled(false);
                    ui->label_status->setText( QString::fromLocal8Bit("已结束配置模式"));
                }

            }
            else if (serialPort::RES_FAILURE == res.getData().getRes())
            {
                errstring =  QString::fromLocal8Bit("配置失败");
                qCritical() << errstring;
                ui->label_status->clear();
                ui->label_status->setText(errstring);
            }
            else
            {
                errstring =  QString::fromLocal8Bit("不知类型错误");
                qCritical() << errstring;
                ui->label_status->clear();
                ui->label_status->setText(errstring);
            }

        } break;

        //获取标签号
        case serialPort::REP_ISPD_ID:
        {
            ui->label_status->clear();
            serialPort::ResPkg<serialPort::ResID> resid(buf.data(), buf.length());
            if (!resid.isValid())
            {
                errstring =  QString::fromLocal8Bit("收到CRC错误");
                qCritical() << errstring;
                ui->label_status->setText(errstring);
                break;
            }
            //将标签号传递到UI
            qint32 ispd_encryt_id = resid.getData().getID();
            QString ispd_encryt_strid = encrypt::encrypt_ispd_id(ispd_encryt_id);
            ui->lineEdit_ispd_no->setText(ispd_encryt_strid);

            //缓存超级板的标签ID号
            ipsd_id_mem = resid.getData().getID();  // add by guosj
    #if 0
            quint32 id = resid.getData().getID();
            QString id_encrypt = encrypt::decimalToAny(id, 34);
            ui->lineEdit_ispd_no->setText(id_encrypt);
    #endif
        } break;

        //获取采样率
        case serialPort::REP_ISPD_HZ:
        {
            ui->label_status->clear();

            serialPort::ResPkg<serialPort::ResHZ> reshz(buf.data(), buf.length());
            if (!reshz.isValid())
            {
                errstring =  QString::fromLocal8Bit("收到CRC错误");
                qCritical() << errstring;
                ui->label_status->setText(errstring);
                break;
            }
            //将采样率传递到UI
            ui->lineEdit_ispd_hz->setText(QString::number(reshz.getData().getHZ()));
        } break;

        //获取心率
        case serialPort::REP_ISPD_HR:
        {
            ui->label_status->clear();
            serialPort::ResPkg<serialPort::ResHR2> reshr(buf.data(), buf.length());
            if (!reshr.isValid())
            {
                errstring =  QString::fromLocal8Bit("收到CRC错误");
                qCritical() << errstring;
                ui->label_status->setText(errstring);
                break;
            }

            quint8 hr = reshr.getData().get_hr();
            //获取心率1-2-3
            QString hr1 = ui->lineEdit_ispd_hr1->text();
            if (hr1.isEmpty())
            {
                ui->lineEdit_ispd_hr1->setText(QString::number(hr));
                break;
            }

            QString hr2 = ui->lineEdit_ispd_hr2->text();
            if (hr2.isEmpty())
            {
                ui->lineEdit_ispd_hr2->setText(QString::number(hr));
                break;
            }

            QString hr3 = ui->lineEdit_ispd_hr3->text();
            if (hr3.isEmpty())
            {
                ui->lineEdit_ispd_hr3->setText(QString::number(hr));
            }
            hr3 = ui->lineEdit_ispd_hr3->text();

            //求取平均心率
            quint8 hr_avg = (hr1.toInt() + hr2.toInt() + hr3.toInt()) / 3;
            ui->lineEdit_ispd_hr_avg->setText(QString::number(hr_avg));

        } break;

        case serialPort::REP_ISPD_SERSOR:
        {
            ui->label_status->clear();
            serialPort::ResPkg<serialPort::Sensor> sensor(buf.data(), buf.length());
            if (!sensor.isValid())
            {
                errstring =  QString::fromLocal8Bit("收到CRC错误");
                qCritical() << errstring;
                ui->label_status->setText(errstring);
                break;
            }

            qint16 ac_x = sensor.getData().get_ac_x();
            qint16 ac_y = sensor.getData().get_ac_y();
            qint16 ac_z = sensor.getData().get_ac_z();
            qint16 gy_x = sensor.getData().get_gy_x();
            qint16 gy_y = sensor.getData().get_gy_y();
            qint16 gy_z = sensor.getData().get_gy_z();
            quint16 hb = sensor.getData().get_hb();
            quint8 pw = sensor.getData().get_pw() & 0x7F;
            quint8 is_charge = sensor.getData().get_pw() & 0x80;
            QString is_charge_str = is_charge == 1 ?  QString::fromLocal8Bit("正在充电") :  QString::fromLocal8Bit("未充电");

            QString ac_pt = "(" + QString::number(ac_x) + ","
                    + QString::number(ac_y) + ","
                    + QString::number(ac_z) + ")";

            QString gy_pt = "(" + QString::number(gy_x) + ","
                    + QString::number(gy_y) + ","
                    + QString::number(gy_z) + ")";

            ui->lineEdit_acc_sp->setText(ac_pt);
            ui->lineEdit_gy_sp->setText(gy_pt);
            ui->lineEdit_hr_sp->setText(QString::number(hb));
            ui->lineEdit_volt_sp->setText(QString::number(pw));
            ui->lineEdit_isCharge->setText(is_charge_str);

            //add by guosj
            serialPort::ReqPkg cus_pkg_rdid(serialPort::REQ_TYPE::ISPD_RD_ID);
            QByteArray send_cus_pkg_rdid = cus_pkg_rdid.toBinary();
            m_spt.write(send_cus_pkg_rdid.data(), send_cus_pkg_rdid.length());
            m_spt.waitForBytesWritten(10);
            //add by guosj end
        } break;

        //获取版本号
        case serialPort::REP_ISPD_VERSION:
        {
            ui->label_status->clear();
            serialPort::ResPkg<serialPort::ResVersion> resversion(buf.data(), buf.length());
            if (!resversion.isValid())
            {
                errstring =  QString::fromLocal8Bit("收到CRC错误");
                qCritical() << errstring;
                ui->label_status->setText(errstring);
                break;
            }

            //将固件版本号传送给UI界面
            QString ispd_version =  QString::fromLocal8Bit("固件") +  QString("%1").arg(resversion.getData().get_ispd_version(),3,10,QChar('0'));
            QString uwb_version =  QString::fromLocal8Bit("透传") + QString("%1").arg(resversion.getData().get_uwb_version(),3,10,QChar('0'));
            QString sp_version =  QString::fromLocal8Bit("协议") + QString("%1").arg(resversion.getData().get_sp_version(),3,10,QChar('0'));
            ui->lineEdit_ispd_version->setText(ispd_version+";"+uwb_version+";"+sp_version);

        } break;

        //一键获取
        case serialPort::REP_ISPD_ALL:
        {
            ui->label_status->clear();
            serialPort::ResPkg<serialPort::ResAll> resall(buf.data(), buf.length());
            if (!resall.isValid())
            {
                errstring =  QString::fromLocal8Bit("收到CRC错误");
                qCritical() << errstring;
                ui->label_status->setText(errstring);
                break;
            }

            //将序列号，采样率，版本号等传送给UI界面
            qint32 ispd_encryt_id = resall.getData().getID();
            QString ispd_encryt_strid = encrypt::encrypt_ispd_id(ispd_encryt_id);
            ui->lineEdit_ispd_no->setText(ispd_encryt_strid);
            ui->lineEdit_ispd_hz->setText(QString::number(resall.getData().getHZ()));
            QString ispd_version =  QString::fromLocal8Bit("固件") +  QString("%1").arg(resall.getData().get_ispd_version(),3,10,QChar('0'));
            QString uwb_version =  QString::fromLocal8Bit("透传") + QString("%1").arg(resall.getData().get_uwb_version(),3,10,QChar('0'));
            QString sp_version =  QString::fromLocal8Bit("协议") + QString("%1").arg(resall.getData().get_sp_version(),3,10,QChar('0'));
            ui->lineEdit_ispd_version->setText(ispd_version+";"+uwb_version+";"+sp_version);
        } break;
    }
}

//解析基站发过来的UDPjson数据
void CheckIspd::onUdpMessage(const QString &json)
{
    QString             msg_json_log;
    QString             list_str;
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8(), &err);
    if (err.error != QJsonParseError::NoError)
    {
        qWarning() << "parse json failed";
        return ;
    }
    msg_json_log = QString(doc.toJson());
    QByteArray ba = msg_json_log.toLatin1();
    char *ch = ba.data();
    qInfo("recive UDP json is:");
    qInfo(ch);
    if (!doc.isObject())
    {
        qWarning() << "not a json object";
        return ;
    }

    QJsonObject json_obj = doc.object();
    if (!json_obj.contains(ISPD_ID))
    {
        qWarning() << "json does not contaion ISPD_ID";
        return ;
    }

    qint32 ispd_id = json_obj[ISPD_ID].toInt();
    if (ispd_id != ipsd_id_mem)
    {
        return ;
    }

    qint32 ac_x = json_obj[ISPD_A_X].toInt();
    qint32 ac_y = json_obj[ISPD_A_Y].toInt();
    qint32 ac_z = json_obj[ISPD_A_Z].toInt();

    qint32 gy_x = json_obj[ISPD_G_X].toInt();
    qint32 gy_y = json_obj[ISPD_G_Y].toInt();
    qint32 gy_z = json_obj[ISPD_G_Z].toInt();

    //心率
    qint32 hb = json_obj[ISPD_HB].toInt();

    //电量
    qint32 pw = json_obj[ISPD_PO].toInt() & 0x7F;

    //加速度
    QString ac_pt = "(" + QString::number(ac_x) + ","
            + QString::number(ac_y) + ","
            + QString::number(ac_z) + ")";

    //陀螺仪
    QString gy_pt = "(" + QString::number(gy_x) + ","
            + QString::number(gy_y) + ","
            + QString::number(gy_z) + ")";

    list_str = "[ ispd_id=" + QString::number(ispd_id) + ",ac_x=" + QString::number(ac_x) + ",ac_y="
           + QString::number(ac_y) + ",ac_z=" + QString::number(ac_z)
           + ",gy_x=" + QString::number(gy_x) + ",gy_y=" + QString::number(gy_y)
           + ",gy_z=" + QString::number(gy_z) + ",hb=" + QString::number(hb)
           + ",pw=" + QString::number(pw) + ",ac_pt=" + ac_pt + ",gy_pt=" + gy_pt + "]";

    ui->textEdit_log->append(list_str);
    //item_list_str = new QStandardItem(list_str);
    //m_model_list_ptr->appendRow(item_list_str);

    ui->lineEdit_acc_mr->setText(ac_pt);
    ui->lineEdit_gy_mr->setText(gy_pt);
    ui->lineEdit_hr_mr->setText(QString::number(hb));
    ui->lineEdit_volt_mr->setText(QString::number(pw));
    ui->pushButton_ispd_cmp->setEnabled(true);
}

void CheckIspd::onTcpMessage(const QString &json)
{

}

//打开串口
void CheckIspd::on_pushButton_open_sp_clicked()
{
    ui->label_status->clear();
    if (m_status_open)
    {
        m_spt.close();
        ui->comboBox_sp->setDisabled(false);
        ui->comboBox_baud->setDisabled(false);
        ui->comboBox_check->setDisabled(false);
        ui->comboBox_data->setDisabled(false);
        ui->comboBox_stop->setDisabled(false);

        m_status_open = false;
        ui->pushButton_customize->setDisabled(true);
        ui->pushButton_applicate->setDisabled(true);

        ui->pushButton_ispd_no->setDisabled(true);
        ui->pushButton_readAll->setDisabled(true);
        ui->pushButton_ispd_version->setDisabled(true);
        ui->pushButton_ispd_hz->setDisabled(true);
        ui->pushButton_ispd_hr->setDisabled(true);
        ui->pushButton_ispd_sensor->setDisabled(true);
        ui->pushButton_ispd_cmp->setDisabled(true);

        ui->lineEdit_ispd_hz->clear();
        ui->lineEdit_ispd_hr1->clear();
        ui->lineEdit_ispd_hr2->clear();
        ui->lineEdit_ispd_hr3->clear();
        ui->lineEdit_ispd_hr_avg->clear();
        ui->lineEdit_ispd_no->clear();
        ui->lineEdit_ispd_version->clear();

        ui->lineEdit_acc_cmp->clear();
        ui->lineEdit_acc_mr->clear();
        ui->lineEdit_acc_sp->clear();

        ui->lineEdit_gy_cmp->clear();
        ui->lineEdit_gy_mr->clear();
        ui->lineEdit_gy_sp->clear();

        ui->lineEdit_hr_cmp->clear();
        ui->lineEdit_hr_mr->clear();
        ui->lineEdit_hr_sp->clear();
        ui->lineEdit_isCharge->clear();

        ui->lineEdit_volt_cmp->clear();
        ui->lineEdit_volt_mr->clear();
        ui->lineEdit_volt_sp->clear();

        ui->pushButton_open_sp->setText(QString::fromLocal8Bit("打开串口"));
        ui->label_status->setText(QString::fromLocal8Bit("串口已关闭"));
    }
    else
    {
        m_spt.setPortName(ui->comboBox_sp->currentText());
        m_spt.setBaudRate(ui->comboBox_baud->currentText().toInt());
        m_spt.setParity(QSerialPort::NoParity);
        m_spt.setDataBits(QSerialPort::Data8);
        m_spt.setStopBits(QSerialPort::OneStop);
        m_spt.close();
        m_spt.setFlowControl(QSerialPort::NoFlowControl);
        if (!m_spt.open(QIODevice::ReadWrite))
        {
            qCritical() << m_spt.error();
            ui->label_status->setText(QString::fromLocal8Bit("打开串口失败"));
            return ;
        }
        ui->label_status->setText(QString::fromLocal8Bit("串口已打开"));

        ui->comboBox_baud->setDisabled(true);
        ui->comboBox_check->setDisabled(true);
        ui->comboBox_data->setDisabled(true);
        ui->comboBox_sp->setDisabled(true);
        ui->comboBox_stop->setDisabled(true);

        ui->pushButton_open_sp->setText(QString::fromLocal8Bit("关闭串口"));
        m_status_open = true;
        ui->pushButton_customize->setEnabled(true);
    }
}

//进入配置模式
void CheckIspd::on_pushButton_customize_clicked()
{
    ui->label_status->clear();
    ui->textEdit_log->clear();
    if (!m_spt.isOpen())
    {
         qWarning() << "serial port not open";
         ui->label_status->setText(QString::fromLocal8Bit("串口没有打开"));
         return ;
    }
    QByteArray pre_array;
    quint8 pre_write = 0xFF;
    quint8 cnt = 15;
    while (cnt--)
    {
        pre_array.append(pre_write);
    }

    qint64 cus_w = m_spt.write(pre_array, pre_array.length());
    if(cus_w == -1)
    {
        ui->label_status->setText(QString::fromLocal8Bit("发送预配置指令失败，请重试..."));
        return ;
    }
    bool cus_ok = m_spt.waitForBytesWritten(10);
    if(cus_ok == false)
    {
        ui->label_status->setText(QString::fromLocal8Bit("发送预配置指令超时，请重试..."));
        return ;
    }
    serialPort::ReqPkg cus_pkg(serialPort::REQ_TYPE::ISPD_MODULE_CUSTOMISE);
    QByteArray send_cus_pkg = cus_pkg.toBinary();
    qint64 cus_one_w = m_spt.write(send_cus_pkg.data(), send_cus_pkg.length());
    if(cus_one_w == -1)
    {
        ui->label_status->setText(QString::fromLocal8Bit("发送开始配置指令失败，请重试..."));
        return ;
    }
    bool cus_one_ok = m_spt.waitForBytesWritten(10);
    if(cus_one_ok == false)
    {
        ui->label_status->setText(QString::fromLocal8Bit("发送开始配置指令超时，请重试..."));
        return ;
    }
    ui->pushButton_customize->setDisabled(true);
    ui->pushButton_applicate->setEnabled(true);
}

//结束配置模式
void CheckIspd::on_pushButton_applicate_clicked()
{
    ui->label_status->clear();
    if (!m_spt.isOpen())
    {
         qWarning() << "serial port not open";
         ui->label_status->setText(QString::fromLocal8Bit("串口没有打开"));
         return ;
    }

    serialPort::ReqPkg app_pkg(serialPort::REQ_TYPE::ISPD_MODULE_APPLICATE);
    QByteArray send_cus_app = app_pkg.toBinary();
    qint64 app_w = m_spt.write(send_cus_app.data(), send_cus_app.length());
    if(app_w == -1)
    {
        ui->label_status->setText(QString::fromLocal8Bit("发送结束配置指令失败，请重试..."));
        return ;
    }
    bool app_ok = m_spt.waitForBytesWritten(10);
    if(app_ok == false)
    {
        ui->label_status->setText(QString::fromLocal8Bit("发送结束配置指令超时，请重试..."));
        return ;
    }
    ui->pushButton_applicate->setEnabled(false);
    ui->pushButton_customize->setEnabled(true);
    ui->pushButton_init->setEnabled(true);
}

//对比数据
void CheckIspd::on_pushButton_ispd_cmp_clicked()
{
    ui->label_status->clear();
    QFont font ("Arial", 20, 75);
    ui->lineEdit_acc_cmp->setFont(font);
    ui->lineEdit_gy_cmp->setFont(font);
    ui->lineEdit_hr_cmp->setFont(font);
    ui->lineEdit_volt_cmp->setFont(font);
    if (ui->lineEdit_acc_sp->text() == ui->lineEdit_acc_mr->text())
    {
        ui->lineEdit_acc_cmp->setText(CMP_SAME);
        ui->lineEdit_acc_cmp->setStyleSheet("color:green");
    }
    else
    {
        ui->lineEdit_acc_cmp->setText(CMP_DIFF);
        ui->lineEdit_acc_cmp->setStyleSheet("color:red");
    }

    if (ui->lineEdit_gy_sp->text() == ui->lineEdit_gy_mr->text())
    {
        ui->lineEdit_gy_cmp->setText(CMP_SAME);
        ui->lineEdit_gy_cmp->setStyleSheet("color:green");
    }
    else
    {
        ui->lineEdit_gy_cmp->setText(CMP_DIFF);
        ui->lineEdit_gy_cmp->setStyleSheet("color:red");
    }

    if (ui->lineEdit_hr_sp->text() == ui->lineEdit_hr_mr->text())
    {
        ui->lineEdit_hr_cmp->setText(CMP_SAME);
        ui->lineEdit_hr_cmp->setStyleSheet("color:green");
    }
    else
    {
        ui->lineEdit_hr_cmp->setText(CMP_DIFF);
        ui->lineEdit_hr_cmp->setStyleSheet("color:red");
    }

    if (ui->lineEdit_volt_sp->text() == ui->lineEdit_volt_mr->text())
    {
        ui->lineEdit_volt_cmp->setText(CMP_SAME);
        ui->lineEdit_volt_cmp->setStyleSheet("color:green");
    }
    else
    {
        ui->lineEdit_volt_cmp->setText(CMP_DIFF);
        ui->lineEdit_volt_cmp->setStyleSheet("color:red");
    }

    if (CMP_SAME == ui->lineEdit_acc_cmp->text() &&
        CMP_SAME == ui->lineEdit_gy_cmp->text() &&
        CMP_SAME == ui->lineEdit_hr_cmp->text() &&
        CMP_SAME == ui->lineEdit_volt_cmp->text())
    {
        ui->pushButton_ispd_cmp->setDisabled(true);
        ui->label_status->setText(CMP_SAME);
    }
    else
    {
        ui->label_status->setText(CMP_DIFF);
    }
}

//获取标签指令
void CheckIspd::on_pushButton_ispd_no_clicked()
{
    ui->label_status->clear();
    if (!m_spt.isOpen())
    {
        qWarning() << "serial port not open";
        ui->label_status->setText(QString::fromLocal8Bit("串口没有打开"));
        return ;
    }

    serialPort::ReqPkg cus_pkg(serialPort::REQ_TYPE::ISPD_RD_ID);
    QByteArray send_cus_pkg = cus_pkg.toBinary();
    qint64 ispd_w = m_spt.write(send_cus_pkg.data(), send_cus_pkg.length());
    if(ispd_w == -1)
    {
        ui->label_status->setText(QString::fromLocal8Bit("获取标签指令发送失败,请重试..."));
        return ;
    }

    bool ispd_ok = m_spt.waitForBytesWritten(10);
    if(ispd_ok == false)
    {
        ui->label_status->setText(QString::fromLocal8Bit("获取标签指令发送超时,请重试..."));
        return ;
    }
    ui->lineEdit_ispd_no->clear();
}

//获取版本号指令
void CheckIspd::on_pushButton_ispd_version_clicked()
{
    ui->label_status->clear();
    if (!m_spt.isOpen())
    {
         qWarning() << "serial port not open";
         ui->label_status->setText(QString::fromLocal8Bit("串口没有打开"));
         return ;
    }
    serialPort::ReqPkg cus_pkg(serialPort::REQ_TYPE::ISPD_RD_VERSION);
    QByteArray send_cus_pkg = cus_pkg.toBinary();
    qint64 ispd_v_w = m_spt.write(send_cus_pkg.data(), send_cus_pkg.length());
    if(ispd_v_w == -1)
    {
        ui->label_status->setText(QString::fromLocal8Bit("发送获取版本号指令失败,请重试..."));
        return ;
    }
    bool ispd_v_ok = m_spt.waitForBytesWritten(10);
    if(ispd_v_ok == false)
    {
        ui->label_status->setText(QString::fromLocal8Bit("发送获取版本号指令超时,请重试..."));
        return ;
    }
    ui->lineEdit_ispd_version->clear();
}

//获取采样率
void CheckIspd::on_pushButton_ispd_hz_clicked()
{
    ui->label_status->clear();
    if (!m_spt.isOpen())
    {
         qWarning() << "serial port not open";
         ui->label_status->setText(QString::fromLocal8Bit("串口没有打开"));
         return ;
    }
    serialPort::ReqPkg cus_pkg(serialPort::REQ_TYPE::ISPD_RD_HZ);
    QByteArray send_cus_pkg = cus_pkg.toBinary();
    qint64 ispd_hz_w = m_spt.write(send_cus_pkg.data(), send_cus_pkg.length());
    if(ispd_hz_w == -1)
    {
        ui->label_status->setText(QString::fromLocal8Bit("发送获取采样率指令错误,请重试..."));
        return ;
    }
    bool ispd_hz_ok = m_spt.waitForBytesWritten(10);
    if(ispd_hz_ok == false)
    {
        ui->label_status->setText(QString::fromLocal8Bit("发送获取采样率指令超时,请重试..."));
        return ;
    }
    ui->lineEdit_ispd_hz->clear();
}

//读取心率指令
void CheckIspd::on_pushButton_ispd_hr_clicked()
{
    ui->label_status->clear();
    if (!m_spt.isOpen())
    {
        qWarning() << "serial port not open";
        ui->label_status->setText(QString::fromLocal8Bit("串口没有打开"));
        return ;
    }

    serialPort::ReqPkg cus_pkg(serialPort::REQ_TYPE::ISPD_RD_HR);
    QByteArray send_cus_pkg = cus_pkg.toBinary();
    qint64 ispd_hr_w = m_spt.write(send_cus_pkg.data(), send_cus_pkg.length());
    if(ispd_hr_w == -1)
    {
        ui->label_status->setText(QString::fromLocal8Bit("发送读取心率指令失败,请重试..."));
        return ;
    }
    bool ispd_hr_ok = m_spt.waitForBytesWritten(10);
    if(ispd_hr_ok == false)
    {
        ui->label_status->setText(QString::fromLocal8Bit("发送读取心率指令超时,请重试..."));
        return ;
    }
    ui->lineEdit_ispd_hr1->clear();
    ui->lineEdit_ispd_hr2->clear();
    ui->lineEdit_ispd_hr3->clear();
    ui->lineEdit_ispd_hr_avg->clear();
}

//一键获取指令
void CheckIspd::on_pushButton_readAll_clicked()
{
    ui->label_status->clear();
    if (!m_spt.isOpen())
    {
        qWarning() << "serial port not open";
        ui->label_status->setText(QString::fromLocal8Bit("串口没有打开"));
        return ;
    }
    serialPort::ReqPkg cus_pkg(serialPort::REQ_TYPE::ISPD_RD_ALL);
    QByteArray send_cus_pkg = cus_pkg.toBinary();
    qint64 read_all_w = m_spt.write(send_cus_pkg.data(), send_cus_pkg.length());
    if(read_all_w == -1)
    {
        ui->label_status->setText(QString::fromLocal8Bit("一键读取指令发送失败,请重试..."));
        return ;
    }
    bool read_all_ok = m_spt.waitForBytesWritten(10);
    if(read_all_ok == false)
    {
        ui->label_status->setText(QString::fromLocal8Bit("一键读取指令发送超时,请重试..."));
        return ;
    }
    ui->lineEdit_ispd_no->clear();
    ui->lineEdit_ispd_hz->clear();
    ui->lineEdit_ispd_version->clear();
}

//获取传感器和电量值
void CheckIspd::on_pushButton_ispd_sensor_clicked()
{
    ui->label_status->clear();
    if (!m_spt.isOpen())
    {
         qWarning() << "serial port not open";
         ui->label_status->setText(QString::fromLocal8Bit("串口没有打开"));
         return ;
    }
    serialPort::ReqPkg cus_pkg(serialPort::REQ_TYPE::ISPD_RD_SENSOR);
    QByteArray send_cus_pkg = cus_pkg.toBinary();
    qint64 ispd_sensor_w = m_spt.write(send_cus_pkg.data(), send_cus_pkg.length());
    if(ispd_sensor_w == -1)
    {
        ui->label_status->setText(QString::fromLocal8Bit("发送获取传感器和电量值指令失败,请重试..."));
        return ;
    }
    bool ispd_sensor_ok = m_spt.waitForBytesWritten(10);
    if(ispd_sensor_ok == false)
    {
        ui->label_status->setText(QString::fromLocal8Bit("发送获取传感器和电量值指令超时,请重试..."));
        return ;
    }
    ui->lineEdit_acc_cmp->clear();
    ui->lineEdit_acc_mr->clear();
    ui->lineEdit_acc_sp->clear();
    ui->lineEdit_gy_cmp->clear();
    ui->lineEdit_gy_mr->clear();
    ui->lineEdit_gy_sp->clear();
    ui->lineEdit_hr_cmp->clear();
    ui->lineEdit_hr_mr->clear();
    ui->lineEdit_hr_sp->clear();
    ui->lineEdit_isCharge->clear();
    ui->lineEdit_volt_cmp->clear();
    ui->lineEdit_volt_mr->clear();
    ui->lineEdit_volt_sp->clear();
}

void CheckIspd::on_pushButton_clicked()
{
    m_spt.setPortName(ui->comboBox_sp->currentText());
    m_spt.setBaudRate(ui->comboBox_baud->currentText().toInt());
    m_spt.setParity(QSerialPort::NoParity);
    m_spt.setDataBits(QSerialPort::Data8);
    m_spt.setStopBits(QSerialPort::OneStop);
    m_spt.close();
    ui->comboBox_sp->setDisabled(false);
    ui->comboBox_baud->setDisabled(false);
    ui->comboBox_check->setDisabled(false);
    ui->comboBox_data->setDisabled(false);
    ui->comboBox_stop->setDisabled(false);

    m_status_open = false;
    ui->pushButton_customize->setDisabled(true);
    ui->pushButton_applicate->setDisabled(true);

    ui->pushButton_ispd_no->setDisabled(true);
    ui->pushButton_readAll->setDisabled(true);
    ui->pushButton_ispd_version->setDisabled(true);
    ui->pushButton_ispd_hz->setDisabled(true);
    ui->pushButton_ispd_hr->setDisabled(true);
    ui->pushButton_ispd_sensor->setDisabled(true);
    ui->pushButton_ispd_cmp->setDisabled(true);

    ui->lineEdit_ispd_hz->clear();
    ui->lineEdit_ispd_hr1->clear();
    ui->lineEdit_ispd_hr2->clear();
    ui->lineEdit_ispd_hr3->clear();
    ui->lineEdit_ispd_hr_avg->clear();
    ui->lineEdit_ispd_no->clear();
    ui->lineEdit_ispd_version->clear();

    ui->lineEdit_acc_cmp->clear();
    ui->lineEdit_acc_mr->clear();
    ui->lineEdit_acc_sp->clear();

    ui->lineEdit_gy_cmp->clear();
    ui->lineEdit_gy_mr->clear();
    ui->lineEdit_gy_sp->clear();

    ui->lineEdit_hr_cmp->clear();
    ui->lineEdit_hr_mr->clear();
    ui->lineEdit_hr_sp->clear();
    ui->lineEdit_isCharge->clear();

    ui->lineEdit_volt_cmp->clear();
    ui->lineEdit_volt_mr->clear();
    ui->lineEdit_volt_sp->clear();

    ui->label_status->setText(QString::fromLocal8Bit("串口已关闭"));
    ui->pushButton_open_sp->setText(QString::fromLocal8Bit("打开串口"));
    this->hide();
    emit goto_genID();
}

void CheckIspd::on_comboBox_sp_activated(const QString &arg1)
{

}

//初始化环境
void CheckIspd::on_pushButton_init_clicked()
{
    mmr_conmunication::udp_data data_tmp;
    mmr_conmunication::udp_data2 read_var_request;
    read_var_request.set_err_code(0);
    mmr_conmunication::udp_message<mmr_conmunication::udp_data2> send_read_pkg(read_var_request, mmr_conmunication::MR_UDP_OPERATOR::read_var);
    QByteArray send_read_request = send_read_pkg.toBinary();
    QByteArray send_res;
    this->ui->label_status->clear();
    QTime timer;
    QHash<uint32_t, QString>::const_iterator index;
    if(this->m_id_ip_map.isEmpty())
    {
        ui->label_status->setText(QString::fromLocal8Bit("没有获取到终端发过来的IP,初始化环境失败,请检查网络环境..."));
        return ;
    }
    else
    {
        for (index = m_id_ip_map.begin(); index != m_id_ip_map.end(); ++index)
        {
            QUdpSocket udp_socket;
            bool bind_is_ok = udp_socket.bind(QHostAddress::Any, 8899, QUdpSocket::ShareAddress);
            if(bind_is_ok == false)
            {
               ui->label_status->setText(QString::fromLocal8Bit("绑定UDP服务器失败,请检查网络..."));
               return ;
            }

            QByteArray recv_msg;
            int len = -1;
            timer.restart();

            while(len = udp_socket.writeDatagram(send_read_request, QHostAddress(index.value()), mmr_conmunication::udp_port_send)
                    , (!udp_socket.waitForReadyRead(1000) || recv_msg.isEmpty()))
            {
                qDebug() << "have writen [" << len << "] bytes to [" << index.value() << ":" << mmr_conmunication::udp_port_send << "]";
                if (timer.elapsed() > (TIMEOUT * 1000))
                {
                    m_err_info = QString::fromLocal8Bit("接收终端数据超时，请重新初始化测试环境！");
                    QString str1 = MESSAGE_RED + m_err_info + MESSAGE_END;
                    QMessageBox::warning(this, QString::fromLocal8Bit("警告"), str1);
                    qDebug() << m_err_info;
                    ui->label_status->setText(m_err_info);
                    return ;
                }
                recv_msg.resize(udp_socket.pendingDatagramSize());
                udp_socket.readDatagram(recv_msg.data(), recv_msg.size());
            }
            mmr_conmunication::udp_message<mmr_conmunication::udp_data> recv_data(recv_msg.data(), recv_msg.size(), mmr_conmunication::MR_UDP_OPERATOR::read_var);
            data_tmp = recv_data.get_data();

            std::string ip = ui->comboBox_mmr_ip->currentText().trimmed().toStdString();  //lineEdit_mmr_ip->text().trimmed().toStdString();
            QVector<qint8> new_domain;
            new_domain.resize(256);
            for (int i = 0; i != ip.size(); i++)
            {
               new_domain[i]=(ip[i]);
            }
            new_domain[ip.size()] = ('\0');

            //update to line model
            mmr_conmunication::udp_data update_data;
            update_data.set_err_code(data_tmp.get_err_code());
            update_data.set_rev(data_tmp.get_rev());
            update_data.set_mr_id(data_tmp.get_mr_id());
            update_data.set_ip(data_tmp.get_ip());
            update_data.set_netmask(data_tmp.get_netmask());
            update_data.set_gateway(data_tmp.get_gateway());
            update_data.set_dns(data_tmp.get_dns());
            update_data.set_mac(data_tmp.get_mac());
            update_data.set_ip_d(data_tmp.get_ip_d());
            update_data.set_netmask_d(data_tmp.get_netmask_d());
            update_data.set_gateway_d(data_tmp.get_gateway_d());
            update_data.set_dns_d(data_tmp.get_dns_d());
            update_data.set_domain(new_domain);
            update_data.set_tcp_port(data_tmp.get_tcp_port());
            update_data.set_udp_port(data_tmp.get_udp_port());
            update_data.set_network_select(2);
            update_data.set_sbs_status_report_interval(data_tmp.get_sbs_status_report_interval());
            update_data.set_manufacturer_message(data_tmp.get_manufacturer_message());
            update_data.set_dip_value(data_tmp.get_dip_value());
            mmr_conmunication::udp_message<mmr_conmunication::udp_data> send_updata_pkg(update_data, mmr_conmunication::MR_UDP_OPERATOR::write_var);
            send_res = send_updata_pkg.toBinary();

            recv_msg.clear();
            len = -1;
            timer.restart();
            while (len = udp_socket.writeDatagram(send_res, QHostAddress(index.value()), mmr_conmunication::udp_port_send)
                   , (!udp_socket.waitForReadyRead(1000) || recv_msg.isEmpty()))
            {

                qDebug() << "have writen [" << len << "] bytes to [" << index.value() << ":" << mmr_conmunication::udp_port_send << "]";

                if (timer.elapsed() > (TIMEOUT * 1000))
                {
                    m_err_info = QString::fromLocal8Bit("接收终端数据超时，请重新初始化测试环境！");
                    QString str1 = MESSAGE_RED + m_err_info + MESSAGE_END;
                    QMessageBox::warning(this, QString::fromLocal8Bit("警告"), str1);
                    qDebug() << m_err_info;
                    return ;
                }
                recv_msg.resize(udp_socket.pendingDatagramSize());
                udp_socket.readDatagram(recv_msg.data(), recv_msg.size());
            }

            //检查更新结果
            mmr_conmunication::udp_message<mmr_conmunication::udp_data2> resp_res(recv_msg.data(), recv_msg.size(), mmr_conmunication::MR_UDP_OPERATOR::read_var);
            quint32 err_code = resp_res.get_data().get_err_code();
            if (0 == err_code)
            {
                m_err_info = QString::fromLocal8Bit("成功更新网络模式[") + QString::number(index.key()) + QString::fromLocal8Bit("]");
            }
            else
            {
                m_err_info = QString::fromLocal8Bit("更新网络模式失败[") + QString::number(index.key()) + QString::fromLocal8Bit("]");
            }
            qDebug() << m_err_info;
            udp_socket.close();

            if (mr_restart(index.value()))
            {
               m_err_info = QString::fromLocal8Bit("[") + QString::number(index.key()) + "]" + QString::fromLocal8Bit("重启成功");
            }
            else
            {
               m_err_info = QString::fromLocal8Bit("[") + QString::number(index.key()) + "]" + QString::fromLocal8Bit("重启失败");
            }
            qDebug() << m_err_info;
        }
        ui->pushButton_init->setEnabled(false);
        ui->label_status->setText(QString::fromLocal8Bit("初始化环境成功"));
    }
}

bool CheckIspd::mr_restart(const QString & ip)
{
    mmr_conmunication::udp_data2 restart_data;
    restart_data.set_err_code(0);
    mmr_conmunication::udp_message<mmr_conmunication::udp_data2> restart_request(restart_data, mmr_conmunication::restart);
    QByteArray send_pkg = restart_request.toBinary();
    QUdpSocket udp_socket;
    bool mr_is_bind_ok = udp_socket.bind(QHostAddress::Any, 8888, QUdpSocket::ShareAddress);
    if(mr_is_bind_ok == false)
    {
       ui->label_status->setText(QString::fromLocal8Bit("绑定UDP服务器失败,请检查网络..."));
       return false;
    }

    QByteArray recv_msg;
    int len = -1;
    while ( len = udp_socket.writeDatagram(send_pkg.data(), send_pkg.size(), QHostAddress(ip), mmr_conmunication::udp_port_send)
           , (!udp_socket.waitForReadyRead(1000) || recv_msg.isEmpty()))
    {
        qDebug() << "have writen [" << len << "] bytes to [" << ip << ":" << mmr_conmunication::udp_port_send << "]";
        recv_msg.resize(udp_socket.pendingDatagramSize());
        udp_socket.readDatagram(recv_msg.data(), recv_msg.size());
    }
    udp_socket.close();

    mmr_conmunication::udp_message<mmr_conmunication::udp_data2> respond_msg(recv_msg.data(), recv_msg.size(), mmr_conmunication::read_var);
    quint32 err_code = respond_msg.get_data().get_err_code();
    if (0 == err_code)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void CheckIspd::on_textEdit_log_windowIconTextChanged(const QString &iconText)
{
    QTextCursor cursor = ui->textEdit_log->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEdit_log->setTextCursor(cursor);
}

