#include "generateid.h"
#include "ui_generateid.h"

#include "common.h"

#include <QCloseEvent>
#include <QDebug>
#include <QDataStream>
#include <QSerialPortInfo>
#include <QDate>
#include <QMessageBox>
#include <QElapsedTimer>

#define MESSAGE_RED "<font size = 200 color = red ><strong>"
#define MESSAGE_GREEN "<font size = 200 color = blue ><strong>"
#define MESSAGE_END "</strong></font>"

//全局变量定义--超时计数器
static int time_count = 0;

//全局变量定义--判断超级板是否有问题的计数器
static int ispd_isbad_count = 0;

GenerateID::GenerateID(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GenerateID)
{
    ui->setupUi(this);
    ui->pushButton_customize->setDisabled(true);
    ui->pushButton_applicate->setDisabled(true);
    ui->pushButton_record->setDisabled(true);
    ui->comboBox_type->setDisabled(true);
    ui->comboBox_color->setDisabled(true);
    ui->comboBox_size->setDisabled(true);
    ui->lineEdit_ispd_id->setDisabled(true);
    ui->pushButton_confirm_hz->setDisabled(true);
    ui->pushButton_test_ispd->setDisabled(true);
    ui->comboBox_hz->setDisabled(true);

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
    connect(&m_spt, SIGNAL(readyRead()), this, SLOT(onRead()));
    m_status_open = false;
    m_is_write_hz = false;
    m_is_write_id = false;
}

GenerateID::~GenerateID()
{
    delete ui;
}

void GenerateID::closeEvent(QCloseEvent *event)
{
    event->accept();
    m_spt.close();
    emit quit();
}

void GenerateID::start()
{
    this->showMaximized();
}

void GenerateID::onUsername(const QString &username)
{
    m_username = username;
}

//录入ID，配置标签ID
void GenerateID::on_pushButton_record_clicked()
{
    ui->label_status->clear();
    if (!m_spt.isOpen())
    {
         qWarning() << "serial port not open";
         ui->label_status->setText(QString::fromLocal8Bit("串口没有打开"));
         return ;
    }
    bool ok;

    m_timeout = startTimer(1000);
    m_current_sign_id = ui->lineEdit_ispd_id->text().toStdString();
    if (this->ui->lineEdit_ispd_id->text() != NULL)
    {
        qint32 ispd_id_dencrypt = encrypt::dencrypt_ispd_id(m_current_sign_id);
        serialPort::IspdID ispd_id(ispd_id_dencrypt, serialPort::REQ_TYPE::ISPD_WR_ID);
        serialPort::ReqMsg<serialPort::IspdID> res_msg(ispd_id);
        QByteArray send_id = res_msg.toBinary();

#if 0
        char *str_bin = send_id.data();
        printf("---------------------\n");
        for (size_t i = 0; i < sizeof((char*)str_bin); ++i)
        {
            printf("%02X ", (char*)str_bin[i]);
            printf("\n");
        }
        printf("---------------------\n");
#endif

        qint64 w_ret = m_spt.write(send_id.data(), send_id.length());
        if(w_ret == -1)
        {
            time_count = 0;
            killTimer(m_timeout);
            QString timeout_info = QString::fromLocal8Bit("发送超级板ID录入指令失败,请重试...！");
            QString str_info = MESSAGE_RED + timeout_info + MESSAGE_END;
            QMessageBox::information(this,QString::fromLocal8Bit("信息"), str_info);
            return ;
        }

        bool w_ok = m_spt.waitForBytesWritten(10);
        if(w_ok == false)
        {
            time_count = 0;
            killTimer(m_timeout);
            QString timeout_info = QString::fromLocal8Bit("发送超级板ID录入指令失败,请重试...！");
            QString str_info = MESSAGE_RED + timeout_info + MESSAGE_END;
            QMessageBox::information(this,QString::fromLocal8Bit("信息"), str_info);
            return ;
        }
        m_is_write_id = true;
    }
    else
    {
        time_count = 0;
        killTimer(m_timeout);
        QString err_info = QString::fromLocal8Bit("输入ID为空,请您务必输入ID...");
        QString str_info = MESSAGE_RED + err_info + MESSAGE_END;
        QMessageBox::information(this,QString::fromLocal8Bit("信息"), str_info);
        qCritical() << err_info;
        return ;
    }

    //write sign_id, ispd_id, date, type, color, size into database
    util::data_base db;
    QString err;
    if (!db.init(err))
    {
        time_count = 0;
        killTimer(m_timeout);
        qCritical() << err;
        return ;
    }

    QString sql = "select user_id from USER where user_name = \"" + m_username + "\"";
    QVariant user_id;
    if (!db.query(sql, user_id, err))
    {
        qCritical() << err;
    }
    m_user_id = user_id.toInt(&ok);
    if (ok)
    {
        qInfo() << "find user_id from the database successfully";
    }
    else
    {
        time_count = 0;
        killTimer(m_timeout);
        QString err_info = QString::fromLocal8Bit("没有在数据库中找到用户信息...");
        QString str_info = MESSAGE_RED + err_info + MESSAGE_END;
        QMessageBox::information(this,QString::fromLocal8Bit("信息"), str_info);
        qCritical() << err_info;
        return ;
    }

    QString ispd_id = QString::fromStdString(m_current_sign_id);

    QDate date(QDate::currentDate());
    int this_year = date.year();
    quint16 year = this_year - 2016;
    quint16 week = date.weekNumber(&(this_year));
    quint16 day  = date.dayOfWeek();
    QString date_time = QString("%1").arg(year, 2, 10, QChar('0'))
            + QString("%1").arg(week, 2, 10, QChar('0'))
            + QString::number(day);

    QString type;
    if(this->ui->comboBox_type->currentText() != NULL)
    {
        type = this->ui->comboBox_type->currentText();
    }

    QString color;
    if (ui->comboBox_color->currentText() == QString::fromLocal8Bit("黑红"))
    {
        color = tr("01");
    }
    else if(ui->comboBox_color->currentText() == QString::fromLocal8Bit("白红"))
    {
        color = tr("02");
    }
    else
    {
        QString color_err = QString::fromLocal8Bit("颜色不匹配");
        qCritical() << color_err;
    }

    QString size;
    if(this->ui->comboBox_size->currentText() == QString::fromLocal8Bit("大"))
    {
        size = tr("20");
    }
    else if(ui->comboBox_size->currentText() == QString::fromLocal8Bit("中"))
    {
        size = tr("10");
    }
    else if(this->ui->comboBox_size->currentText() == QString::fromLocal8Bit("小"))
    {
        size = tr("05");
    }
    else
    {
        QString color_err = QString::fromLocal8Bit("大小类型不匹配");
        qCritical() << color_err;
    }

    QString sn = date_time + type + color + size + ispd_id;
    qInfo() << "sn :"  << sn;

    sql = "INSERT INTO ISPD (user_id, ispd_id, date, type, color, size, sn) VALUES ("
            + QString::number(m_user_id) + ","
            + "\"" + ispd_id + "\"" + ","
            + "\"" + date_time + "\"" + ","
            + "\"" + type + "\"" + ","
            + "\"" + color + "\"" + ","
            + "\"" + size + "\"" + ","
            + "\"" + sn + "\""+ ")";
    if (!db.update(sql, err))
    {
        time_count = 0;
        killTimer(m_timeout);
        QString error_msg = QString::fromLocal8Bit("数据库写入信息失败！");
        QString str_info = MESSAGE_RED + error_msg + MESSAGE_END;
        QMessageBox::warning(this, QString::fromLocal8Bit("警告"), str_info);
        qCritical() << error_msg  << "{"<< err << "}";
        return ;
    }

    if (err.isEmpty())
    {
        ui->label_status->setText(QString::fromLocal8Bit("数据库录入完毕！"));
        ui->lineEdit_ispd_id->clear();
    }    
}

//打开串口/关闭串口
void GenerateID::on_pushButton_open_sp_clicked()
{
    ui->label_status->clear();
    if (m_status_open)
    {
        m_spt.close();   //关闭串口
        ui->comboBox_baud->setDisabled(false);
        ui->comboBox_check->setDisabled(false);
        ui->comboBox_data->setDisabled(false);
        ui->comboBox_sp->setDisabled(false);
        ui->comboBox_stop->setDisabled(false);
        m_status_open = false;
        ui->pushButton_customize->setDisabled(true);
        ui->pushButton_applicate->setDisabled(true);
        ui->pushButton_record->setDisabled(true);
        ui->comboBox_type->setDisabled(true);
        ui->comboBox_color->setDisabled(true);
        ui->comboBox_size->setDisabled(true);
        ui->pushButton_confirm_hz->setDisabled(true);
        ui->comboBox_hz->setDisabled(true);
        ui->lineEdit_ispd_id->clear();
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

void GenerateID::timerEvent(QTimerEvent *ev)
{
    if(ev->timerId() == m_timeout)
    {
        time_count++;
        if(time_count == 10)
        {
           time_count = 0;
           ispd_isbad_count++;
           QString timeout_info = QString::fromLocal8Bit("收发数据超时，请重试...");
           QString str1 = MESSAGE_RED + timeout_info + MESSAGE_END;
           QMessageBox::information(this,QString::fromLocal8Bit("信息"), str1);
           if(ispd_isbad_count == 3)
           {
               ispd_isbad_count = 0;
               QString bad_info = QString::fromLocal8Bit("你测试的超级板通信存在问题，请换个ID号重新录入或者返工重做...");
               QString bad_str = MESSAGE_RED + bad_info + MESSAGE_END;
               QMessageBox::information(this,QString::fromLocal8Bit("信息"), bad_str);
           }
           killTimer(m_timeout);
        }
        QString info = QString::fromLocal8Bit("请等待") + QString::number(time_count)+QString::fromLocal8Bit("数据收发中...");
        ui->label_status ->setText(info);
    }
}

void GenerateID::onRead()
{
    m_spt.waitForReadyRead(100);
    QByteArray buf = m_spt.readAll();
    if (buf.length() < 5)
    {
        QString rw_info = QString::fromLocal8Bit("读取超级发过来的数据失败，请重试...");
        QString rw_str = MESSAGE_RED + rw_info + MESSAGE_END;
        QMessageBox::information(this,QString::fromLocal8Bit("信息"), rw_str);
        return ;
    }

    //超时处理
    time_count = 0;
    killTimer(m_timeout);

    qDebug() << QString::fromLocal8Bit("护腿板发过来的数据长度size =") << buf.size();
    qDebug() << QString::fromLocal8Bit("护腿板发过来的数据recv buf = ") << buf;

    serialPort::REP_TYPE type = static_cast<serialPort::REP_TYPE>(buf.at(2));
    QString errstring;
    serialPort::ResPkg<serialPort::ResResult> res(buf.data(), buf.length());
    switch (type)
    {
        ui->label_status->clear();
        case serialPort::REP_ERR:
        {
            if (serialPort::ERR_CRC == res.getData().getRes())
            {
                errstring = QString::fromLocal8Bit("CRC出错");
                qCritical() << errstring;
                ui->label_status->setText(errstring);
            }
            else if (serialPort::ERR_FRM == res.getData().getRes())
            {
                errstring = QString::fromLocal8Bit("帧类型出错");
                qCritical() << errstring;
                ui->label_status->setText(errstring);
            }
            else
            {
                errstring = QString::fromLocal8Bit("不知类型错误");
                qCritical() << errstring;
                ui->label_status->setText(errstring);
            }
        } break;

        case serialPort::REP_WR_RES:
        {
            if (serialPort::RES_SUCCESS == res.getData().getRes())
            {
                errstring = QString::fromLocal8Bit("配置成功");
                qDebug() << errstring;
                ui->lineEdit_ispd_id->clear();
                ui->label_status->setText(errstring);

                if (m_is_write_hz)
                {
                    ui->label_status->setText(QString::fromLocal8Bit("采样率配置成功！"));
                    m_is_write_hz = false;
                    break ;
                }

                if (m_is_write_id)
                {
                    ui->label_status->setText(QString::fromLocal8Bit("超级板ID录入成功！"));
                    m_is_write_id = false;
                    break ;
                }

                if (!ui->pushButton_customize->isEnabled())
                {
                    ui->pushButton_applicate->setEnabled(true);
                    ui->pushButton_record->setEnabled(true);
                    ui->comboBox_hz->setEnabled(true);
                    ui->label_status->setText(QString::fromLocal8Bit("已进入配置模式"));
                    break ;
                }

                if(!ui->pushButton_applicate->isEnabled())
                {
                    ui->pushButton_customize->setEnabled(true);
                    ui->pushButton_record->setDisabled(true);
                    ui->pushButton_confirm_hz->setDisabled(true);
                    ui->comboBox_hz->setDisabled(true);
                    ui->label_status->setText(QString::fromLocal8Bit("已结束配置"));
                    break ;
                }

            }
            else if (serialPort::RES_FAILURE == res.getData().getRes())
            {
                errstring = QString::fromLocal8Bit("配置失败");
                qCritical() << errstring;
                ui->label_status->clear();
                ui->label_status->setText(errstring);
            }
            else
            {
                errstring = QString::fromLocal8Bit("不知类型错误");
                qCritical() << errstring;
                ui->label_status->clear();
                ui->label_status->setText(errstring);
            }
        } break;
     }
}

//高级应用---确认
void GenerateID::on_pushButton_confirm_hz_clicked()
{
    ui->label_status->clear();
    if (!m_spt.isOpen())
    {
         qWarning() << "serial port not open";
         ui->label_status->setText(QString::fromLocal8Bit("串口没有打开"));
         return ;
    }

    m_timeout = startTimer(1000); //超时处里
    quint8 hz = ui->comboBox_hz->currentText().toInt();
    serialPort::IspdHZ ispd_hz(hz, serialPort::REQ_TYPE::ISPD_WR_HZ);
    serialPort::ReqMsg<serialPort::IspdHZ> res_msg(ispd_hz);
    QByteArray send_hz = res_msg.toBinary();
    qint64 hz_ret = m_spt.write(send_hz.data(), send_hz.length());
    if(hz_ret == -1)
    {
        time_count = 0;
        killTimer(m_timeout);
        QString bad_info = QString::fromLocal8Bit("发送更新采样率指令失败,请重试...");
        QString bad_str = MESSAGE_RED + bad_info + MESSAGE_END;
        QMessageBox::information(this,QString::fromLocal8Bit("信息"), bad_str);
        return ;
    }

    bool hz_timeout  = m_spt.waitForBytesWritten(10);
    if(hz_timeout == false)
    {
        time_count = 0;
        killTimer(m_timeout);
        QString bad_info = QString::fromLocal8Bit("发送更新采样率指令失败,请重试...");
        QString bad_str = MESSAGE_RED + bad_info + MESSAGE_END;
        QMessageBox::information(this,QString::fromLocal8Bit("信息"), bad_str);
        return ;
    }
    m_is_write_hz = true;
}

//开始配置
void GenerateID::on_pushButton_customize_clicked()
{
    ui->label_status->clear();
    if (!m_spt.isOpen())
    {
         qWarning() << "serial port is not open";
         ui->label_status->setText(QString::fromLocal8Bit("串口没有打开"));
         return ;
    }
    m_timeout = startTimer(1000);
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
        time_count = 0;
        killTimer(m_timeout);
        QString bad_info = QString::fromLocal8Bit("发送预配置指令失败,请重试...");
        QString bad_str = MESSAGE_RED + bad_info + MESSAGE_END;
        QMessageBox::information(this,QString::fromLocal8Bit("信息"), bad_str);
        return ;
    }
    bool cus_ok = m_spt.waitForBytesWritten(10);
    if(cus_ok == false)
    {
        time_count = 0;
        killTimer(m_timeout);
        QString bad_info = QString::fromLocal8Bit("发送预配置指令失败,请重试...");
        QString bad_str = MESSAGE_RED + bad_info + MESSAGE_END;
        QMessageBox::information(this,QString::fromLocal8Bit("信息"), bad_str);
        return ;
    }

    serialPort::ReqPkg cus_pkg(serialPort::REQ_TYPE::ISPD_MODULE_CUSTOMISE);
    QByteArray send_cus_pkg = cus_pkg.toBinary();
    qint64 cus_one_w =  m_spt.write(send_cus_pkg.data(), send_cus_pkg.length());
    if(cus_one_w == -1)
    {
        time_count = 0;
        killTimer(m_timeout);
        QString bad_info = QString::fromLocal8Bit("开始配置失败,请重试...");
        QString bad_str = MESSAGE_RED + bad_info + MESSAGE_END;
        QMessageBox::information(this,QString::fromLocal8Bit("信息"), bad_str);
        return ;
    }

    bool cus_one_ok = m_spt.waitForBytesWritten(10);
    if(cus_one_ok == false)
    {
        time_count = 0;
        killTimer(m_timeout);
        QString bad_info = QString::fromLocal8Bit("开始配置失败,请重试...");
        QString bad_str = MESSAGE_RED + bad_info + MESSAGE_END;
        QMessageBox::information(this,QString::fromLocal8Bit("信息"), bad_str);
        return ;
    }

    //ui setting
    ui->pushButton_customize->setDisabled(true);
    ui->pushButton_applicate->setEnabled(true);
    ui->pushButton_record->setEnabled(true);
    ui->comboBox_type->setEnabled(true);
    ui->comboBox_color->setEnabled(true);
    ui->comboBox_size->setEnabled(true);
    ui->lineEdit_ispd_id->setEnabled(true);
}

//结束配置
void GenerateID::on_pushButton_applicate_clicked()
{
    ui->label_status->clear();
    if (!m_spt.isOpen())
    {
         qWarning() << "serial port not open";
         ui->label_status->setText(QString::fromLocal8Bit("串口没有打开"));
         return ;
    }

    m_timeout = startTimer(1000); //超时处里

    serialPort::ReqPkg app_pkg(serialPort::REQ_TYPE::ISPD_MODULE_APPLICATE);
    QByteArray send_cus_app = app_pkg.toBinary();
    qint64 app_w = m_spt.write(send_cus_app.data(), send_cus_app.length());
    if(app_w == -1)
    {        
        time_count = 0;
        killTimer(m_timeout);
        QString bad_info = QString::fromLocal8Bit("发送结束配置指令失败,请重试...");
        QString bad_str = MESSAGE_RED + bad_info + MESSAGE_END;
        QMessageBox::information(this,QString::fromLocal8Bit("信息"), bad_str);
        return ;
    }
    bool app_ok = m_spt.waitForBytesWritten(10);
    if(app_ok == false)
    {
        time_count = 0;
        killTimer(m_timeout);
        QString bad_info = QString::fromLocal8Bit("发送结束配置指令失败,请重试...");
        QString bad_str = MESSAGE_RED + bad_info + MESSAGE_END;
        QMessageBox::information(this,QString::fromLocal8Bit("信息"), bad_str);
        return ;
    }

    //ui setting
    ui->pushButton_applicate->setDisabled(true);
    ui->pushButton_customize->setDisabled(false);
    ui->comboBox_type->setDisabled(true);
    ui->comboBox_color->setDisabled(true);
    ui->comboBox_size->setDisabled(true);
    ui->lineEdit_ispd_id->setDisabled(true);
}

void GenerateID::on_comboBox_hz_currentIndexChanged(const QString &arg1)
{
    ui->label_status->clear();
    ui->pushButton_confirm_hz->setEnabled(true);
    ui->label_status->setText(QString::fromLocal8Bit("采样率已更新"));
}

void GenerateID::on_pushButton_test_ispd_clicked()
{
    //add by guosj
    m_spt.setPortName(ui->comboBox_sp->currentText());
    m_spt.setBaudRate(ui->comboBox_baud->currentText().toInt());
    m_spt.setParity(QSerialPort::NoParity);
    m_spt.setDataBits(QSerialPort::Data8);
    m_spt.setStopBits(QSerialPort::OneStop);
    ui->label_status->setText(QString::fromLocal8Bit("串口已关闭"));
    ui->pushButton_open_sp->setText(QString::fromLocal8Bit("打开串口"));
    //add by guosj end
    m_spt.close();
    ui->comboBox_baud->setDisabled(false);
    ui->comboBox_check->setDisabled(false);
    ui->comboBox_data->setDisabled(false);
    ui->comboBox_sp->setDisabled(false);
    ui->comboBox_stop->setDisabled(false);
    m_status_open = false;
    ui->pushButton_customize->setDisabled(true);
    ui->pushButton_applicate->setDisabled(true);
    ui->pushButton_record->setDisabled(true);
    ui->comboBox_type->setDisabled(true);
    ui->comboBox_color->setDisabled(true);
    ui->comboBox_size->setDisabled(true);
    ui->pushButton_confirm_hz->setDisabled(true);
    ui->comboBox_hz->setDisabled(true);
    ui->lineEdit_ispd_id->clear();
    this->hide();
    emit goto_checkISPD();
}


void GenerateID::on_lineEdit_ispd_id_editingFinished()
{

}

void GenerateID::on_comboBox_hz_currentIndexChanged(int index)
{

}

void GenerateID::on_comboBox_hz_activated(const QString &arg1)
{

}
