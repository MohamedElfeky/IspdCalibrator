#include "../hdtasparser/hdtasparser/hdtasparser.h"
#include "../hdtasparser/hdtasparser/utility.h"

#include "worker.h"
#include "common.h"

#include <QThread>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDateTime>

Worker::Worker(QObject *parent) : QObject(parent) {}

Worker::~Worker() {}

void Worker::setupWorker(QThread * thread) {
    connect(thread, SIGNAL(started()), this, SLOT(dowork()));
}


// udp_worker
udp_worker::udp_worker(QObject * parent) :
    Worker(parent)
{}

udp_worker::~udp_worker() {
    m_udp_socket_ptr->close();
    //delete m_udp_socket_ptr;
    m_udp_socket_ptr->deleteLater();
}

void udp_worker::dowork() {
    m_udp_socket_ptr = new QUdpSocket(this);
    if (!m_udp_socket_ptr) {
        // log here
        qFatal("can not assign memory any more");
        return ;
    }

    if (!m_udp_socket_ptr->bind(QHostAddress::Any, udp_port, QUdpSocket::ShareAddress)) {
        // log here
        qCritical() << "udp bind failed";
        return ;
    }

    qInfo() << "udp server starts listening port [" << udp_port << "]";
    connect(m_udp_socket_ptr, SIGNAL(readyRead()), this, SLOT(handle_connections()));
}

static QVector<QJsonObject> 	json_obj_mr_pb_array;

void udp_worker::handle_connections()
{
    QByteArray res;
    res.resize(m_udp_socket_ptr->pendingDatagramSize());
    QHostAddress 	client_ip;
    quint16 		client_port;
    m_udp_socket_ptr->readDatagram(res.data(), res.size(), &client_ip, &client_port);

    // verify udp data type
    hdtas::HdtasPackage package;
    size_t length = 0;
    package.Unpack(reinterpret_cast<const unsigned char *>(res.constData()),
                   static_cast<size_t>(res.size()),
                   length);
    device_mr_id 	mmr_id 	= package.GetMMrID();
    QString 		mmr_id_s= (hdtas::utility::int_2_hex(mmr_id)).c_str();
    h_uint 			msg_id  = package.GetMsgID();
    h_uint			pack_id	= package.GetPackageID();
    h_uint			pack_cnt= package.GetPackageCount();
    QByteArray	 	err_str	= package.GetErrorString();

    hdtas::HdtasMessage message;
    message.Deserialize(&package);
    device_mr_id 	mmr_id_from_msg 	= message.GetMMrID();
    QString		 	mmr_id_from_msg_s 	= (hdtas::utility::int_2_hex(mmr_id_from_msg)).c_str();
    h_uint 			msg_id_from_msg		= package.GetMsgID();
    QByteArray	 	err_str_from_msg	= package.GetErrorString();
    hdtas::HDTAS_MSG_TYPE msg_type 		= message.GetType();

    QJsonDocument 			json_doc;
    switch(msg_type)
    {
        case hdtas::HDTAS_MSG_TYPE::HMT_ISPD:
        {
            hdtas::HdtasIspdData ispd_data;
            ispd_data.Deserialize(&message);
            hdtas::ispd_date_time time 			= ispd_data.GetTimestamp();
            hdtas::isdp_data_array ispd_array 	= ispd_data.GetDataInfo();

            QJsonObject json_obj_ispd;
            //for (auto elem : ispd_array)
            for(unsigned int i = 0; i < ispd_array.size(); i++)
            {
                //json_obj_ispd.insert(UDPTYPE, 1);
                json_obj_ispd.insert(ISPD_ID, hdtas::utility::int_2_hex(ispd_array[i].id).c_str());
                json_obj_ispd.insert(ISPD_HB, static_cast<qint64>(ispd_array[i].heart_rate));
                json_obj_ispd.insert(ISPD_CH, static_cast<qint64>(ispd_array[i].charge));
                json_obj_ispd.insert(ISPD_PO, static_cast<qint64>(ispd_array[i].power));
                json_obj_ispd.insert(ISPD_TS, QString().append(time.h).append(":").append(time.n).append(":").append(time.s).append(":").append(time.ms));
                // send to display
                json_doc.setObject(json_obj_ispd);
                emit sendUdpMessage(json_doc.toJson(QJsonDocument::Compact));
            }//end for
        }break;
        case hdtas::HDTAS_MSG_TYPE::HMT_MR_STU:
        {
            hdtas::HdtasMrStatus mr_status_data;
            mr_status_data.Deserialize(&message);
            {
                QJsonObject json_obj_tmp;
                json_obj_tmp.insert(MR_ID, hdtas::utility::int_2_hex(message.GetMMrID()).c_str());
                if (json_obj_mr_pb_array.isEmpty()) {
                    json_obj_mr_pb_array.append(json_obj_tmp);
                }
            }

            hdtas::mr_status_array mr_array 	= mr_status_data.GetStatusInfo();
            //for (auto elem : mr_array)
            for(unsigned int i = 0; i < mr_array.size(); i++)
            {
                QJsonObject json_obj;
                json_obj.insert(MR_ID, hdtas::utility::int_2_hex(mr_array[i].id).c_str());
                //json_obj.insert(MR_STATUS, elem.status);
                if (!json_obj_mr_pb_array.contains(json_obj)) {
                     json_obj_mr_pb_array.append(json_obj);
                }
            }// end for
        }break;

        case hdtas::HDTAS_MSG_TYPE::HMT_PB_STU:
        {
            hdtas::HdtasPbStatus pb_status_data;
            pb_status_data.Deserialize(&message);

            device_mr_id mr_id = pb_status_data.GetMrID();
            hdtas::power_board_status pb_status = pb_status_data.GetStatusInfo();
            hdtas::power_board_status_group pb_status_group = pb_status_data.GetStatusGroupInfo();

            // optimize here--remove found elements
            //for (auto elem : json_obj_mr_pb_array)
            for(unsigned int i = 0; i < json_obj_mr_pb_array.size(); i++)
            {
                if(hdtas::utility::int_2_hex(mr_id).c_str() == json_obj_mr_pb_array[i].value(MR_ID).toString())
                {
                    json_obj_mr_pb_array[i].insert(PB_SWITCH, pb_status.switch_);
                    json_obj_mr_pb_array[i].insert(PB_SWITCH_V, pb_status_group.switch_.first);
                    json_obj_mr_pb_array[i].insert(PB_SWITCH_C, pb_status_group.switch_.second);
                    json_obj_mr_pb_array[i].insert(PB_ROUTER, pb_status.router_);
                    json_obj_mr_pb_array[i].insert(PB_ROUTER_V, pb_status_group.router_.first);
                    json_obj_mr_pb_array[i].insert(PB_ROUTER_C, pb_status_group.router_.second);
                    json_obj_mr_pb_array[i].insert(PB_LOCATE, pb_status.locate_);
                    json_obj_mr_pb_array[i].insert(PB_LOCATE_V, pb_status_group.locate_.first);
                    json_obj_mr_pb_array[i].insert(PB_LOCATE_C, pb_status_group.locate_.second);
                    json_obj_mr_pb_array[i].insert(PB_MICROPHONE, pb_status.microphone_);
                    json_obj_mr_pb_array[i].insert(PB_CAMERA, pb_status.camera_);
                    json_obj_mr_pb_array[i].insert(PB_CAMERA_V, pb_status_group.camera_.first);
                    json_obj_mr_pb_array[i].insert(PB_CAMERA_C, pb_status_group.camera_.second);
                    json_obj_mr_pb_array[i].insert(PB_PRELOAD, pb_status.preload_);
                    json_obj_mr_pb_array[i].insert(PB_PRELOAD_V, pb_status_group.preload_.first);
                    json_obj_mr_pb_array[i].insert(PB_PRELOAD_C, pb_status_group.preload_.second);
                    json_obj_mr_pb_array[i].insert(PB_SOURCE, pb_status.source_);
                    json_obj_mr_pb_array[i].insert(PB_BATTERY_STU, pb_status.battery_status_);
                    json_obj_mr_pb_array[i].insert(PB_BATTERY_CH, pb_status.battery_charge_);
                    json_obj_mr_pb_array[i].insert(PB_BATTERY_CON, pb_status.battery_connect_);
                    json_obj_mr_pb_array[i].insert(PB_BATTERY_CTL, pb_status.battery_control_);
                    json_obj_mr_pb_array[i].insert(PB_BATTERY_V, pb_status_group.battery_.first);
                    json_obj_mr_pb_array[i].insert(PB_BATTERY_C, pb_status_group.battery_.second);
                    json_obj_mr_pb_array[i].insert(PB_NET, pb_status.internet_);

                    json_doc.setObject(json_obj_mr_pb_array[i]);
                    emit sendUdpMessage(json_doc.toJson(QJsonDocument::Compact));
                }
            }//end for
        }break;

        case hdtas::HDTAS_MSG_TYPE::HMT_UNKNOWN:
        {
            qDebug() << "unknown hdtas message type";
        }break;

    }// end switch

    qDebug() << "udp connected [" << client_ip.toString() << ":" << client_port << "]"
            << ", message(" << res.size() <<  ")[" << res << "]";
    //emit(sendUdpMessage("udp signal send: " + res));

}

// serial port udp
serialport_udp_worker::serialport_udp_worker(QObject *parent)
    : Worker(parent)
{ }

serialport_udp_worker::~serialport_udp_worker()
{
    m_udp_socket_ptr->close();
    m_udp_socket_ptr->deleteLater();
}

void serialport_udp_worker::dowork()
{
    m_udp_socket_ptr = new QUdpSocket(this);
    if (!m_udp_socket_ptr) {
        // log here
        qFatal("can not assign memory any more");
        return ;
    }

    if (!m_udp_socket_ptr->bind(QHostAddress::Any, udp_port, QUdpSocket::ShareAddress)) {
        // log here
        qCritical() << "udp bind failed";
        return ;
    }

    qInfo() << "udp server starts listening port [" << udp_port << "]";
    connect(m_udp_socket_ptr, SIGNAL(readyRead()), this, SLOT(handle_connections()));
}

void serialport_udp_worker::handle_connections()
{
    QByteArray res;
    res.resize(m_udp_socket_ptr->pendingDatagramSize());
    QHostAddress 	client_ip;
    quint16 		client_port;
    m_udp_socket_ptr->readDatagram(res.data(), res.size(), &client_ip, &client_port);
    //verify udp data type
    hdtas::HdtasPackage package;
    size_t length = 0;
    package.Unpack(reinterpret_cast<const unsigned char *>(res.constData()),
                   static_cast<size_t>(res.size()),
                   length);
    device_mr_id 	mmr_id 	= package.GetMMrID();
    QString 		mmr_id_s= (hdtas::utility::int_2_hex(mmr_id)).c_str();
    h_uint 			msg_id  = package.GetMsgID();
    h_uint			pack_id	= package.GetPackageID();
    h_uint			pack_cnt= package.GetPackageCount();
    QByteArray	 	err_str	= package.GetErrorString();

    hdtas::HdtasMessage message;
    message.Deserialize(&package);
    device_mr_id 	mmr_id_from_msg 	= message.GetMMrID();
    QString		 	mmr_id_from_msg_s 	= (hdtas::utility::int_2_hex(mmr_id_from_msg)).c_str();
    h_uint 			msg_id_from_msg		= package.GetMsgID();
    QByteArray	 	err_str_from_msg	= package.GetErrorString();
    hdtas::HDTAS_MSG_TYPE msg_type 		= message.GetType();


    QString msg_log_str  = "mmr_id=" + QString::number(mmr_id) + " mmr_id_s=" + mmr_id_s +
            ", msg_id=" + QString::number(msg_id) + ", pack_id=" + QString::number(pack_id)
            + ", pack_cnt=" + QString::number(pack_cnt) + ", err_str=" + err_str.data()
            + ", mmr_id_from_msg=" + QString::number(mmr_id_from_msg)
            + ", mmr_id_from_msg_s=" + mmr_id_from_msg_s + ",msg_id_from_msg=" + QString::number(msg_id_from_msg)
            + ", err_str_from_msg=" + err_str_from_msg.data();


    //qInfo("read Datagram from MMR is:");
    QByteArray ba = msg_log_str.toLatin1();
    char *ch = ba.data();
    //qInfo(ch);
    switch(msg_type)
    {
        case hdtas::HDTAS_MSG_TYPE::HMT_ISPD:
        {
            hdtas::HdtasIspdData ispd_data;
            ispd_data.Deserialize(&message);
            hdtas::ispd_date_time time = ispd_data.GetTimestamp();
            hdtas::isdp_data_array ispd_array = ispd_data.GetDataInfo();
            QJsonDocument 	json_doc;
            QJsonObject     json_obj_ispd;
            //for (auto elem : ispd_array)
            for(unsigned int i = 0; i < ispd_array.size(); i++)
            {

                if(!ispd_array[i].isContainSensor)
                {
                    QDateTime time = QDateTime::currentDateTime();
                    QString time_str = time.toString("yyyy-MM-dd hh:mm:ss ddd");
                    QString device_ispd_id = QString::number(static_cast<qint32>(ispd_array[i].id));
                    QString log_str = QString::fromLocal8Bit("收到UDP数据成功,但数据中没有包含传感器的数据 ") + ", ispd_id=" + device_ispd_id + ", "+ time_str;
                    //qCritical("recive UDP data,but do not include sensor data");
                    emit sendUdpLogMessage(log_str);
                    return ;
                }

                //qDebug() << "---hear rate from master station--- : " << ispd_array[i].heart_rate;
                json_obj_ispd.insert(ISPD_ID, static_cast<qint32>(ispd_array[i].id));
                json_obj_ispd.insert(ISPD_HB, static_cast<qint32>(ispd_array[i].heart_rate));
                json_obj_ispd.insert(ISPD_CH, static_cast<qint32>(ispd_array[i].charge));
                json_obj_ispd.insert(ISPD_PO, static_cast<qint32>(ispd_array[i].power));
                json_obj_ispd.insert(ISPD_A_X, static_cast<qint32>(ispd_array[i].acceleration.x));
                json_obj_ispd.insert(ISPD_A_Y, static_cast<qint32>(ispd_array[i].acceleration.y));
                json_obj_ispd.insert(ISPD_A_Z, static_cast<qint32>(ispd_array[i].acceleration.z));
                json_obj_ispd.insert(ISPD_G_X, static_cast<qint32>(ispd_array[i].gyroscope.x));
                json_obj_ispd.insert(ISPD_G_Y, static_cast<qint32>(ispd_array[i].gyroscope.y));
                json_obj_ispd.insert(ISPD_G_Z, static_cast<qint32>(ispd_array[i].gyroscope.z));
                json_doc.setObject(json_obj_ispd);
                emit sendUdpMessage(json_doc.toJson(QJsonDocument::Compact));
            }
        }
        break;

    default:
        //qInfo("message data type do not match");
        hdtas::HdtasIspdData ispd_data;
        ispd_data.Deserialize(&message);
        hdtas::isdp_data_array ispd_array = ispd_data.GetDataInfo();
        //for (auto elem : ispd_array)
        for(unsigned int i = 0; i < ispd_array.size(); i++)
        {
            QDateTime time = QDateTime::currentDateTime();
            QString time_str = time.toString("yyyy-MM-dd hh:mm:ss ddd");
            QString device_ispd_id = QString::number(static_cast<qint32>(ispd_array[i].id));
            QString def_log_str = QString::fromLocal8Bit("收到UDP数据成功,但消息的数据类型不匹配") + ", ispd_id=" + device_ispd_id + ", " + time_str;
            emit sendUdpDefaultMsg(def_log_str);
        }
    }

    hdtas::HdtasIspdData ispd_data;
    ispd_data.Deserialize(&message);
    hdtas::ispd_date_time time = ispd_data.GetTimestamp();
    hdtas::isdp_data_array ispd_array = ispd_data.GetDataInfo();
    //for (auto elem : ispd_array)
    for(unsigned int i = 0; i < ispd_array.size(); i++)
    {
        QDateTime time = QDateTime::currentDateTime();
        QString time_str = time.toString("yyyy-MM-dd hh:mm:ss ddd");
        QString device_ispd_id = QString::number(static_cast<qint32>(ispd_array[i].id));
        QString udp_data = QString::fromLocal8Bit("收到UDP全部数据成功:") + "ispd_id=" + device_ispd_id + ", " + time_str;
        emit sendUdpData(udp_data);
    }
}
