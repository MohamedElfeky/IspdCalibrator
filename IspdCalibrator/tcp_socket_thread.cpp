#include "tcp_socket_thread.h"

#include "../hdtasparser/hdtasparser/hdtasparser.h"
#include "../hdtasparser/hdtasparser/utility.h"

#include "common.h"

#include <QDataStream>
#include <QHostAddress>
#include <QByteArray>
#include <QString>
#include <string>
#include <QVariant>


// build send json
struct sub_mr {
    device_mr_id 					mr_id;
    h_uint16						mr_is_online;
    h_uint							pb_ar_int;
    hdtas::HDTAS_OC_STATUS			pb_is_ar;
    hdtas::power_board_status 		pb_stu;
    hdtas::power_board_status_group pb_stu_group;
};

struct build_json {
    device_mr_id 			mmr_id;
    h_uint					mr_ar_int;
    hdtas::HDTAS_OC_STATUS	mr_is_ar;
    QVector<sub_mr>			mmr_sub;

    QString toJson();
};

QString build_json::toJson() {
    QJsonObject json_obj;
    json_obj.insert(MMR_ID, hdtas::utility::int_2_hex(mmr_id).c_str());
    json_obj.insert(MR_AUTO_REPORT_INTERVAL, static_cast<qint64>(mr_ar_int));
    json_obj.insert(MR_IS_AR, mr_is_ar == hdtas::HDTAS_OC_STATUS::HOCS_OPEN ? true : false);
    QJsonObject obj_temp;
    foreach (sub_mr elem, mmr_sub) {
        obj_temp.insert(MR_ID, static_cast<qint64>(elem.mr_id));
        obj_temp.insert(MR_STATUS_INFO, elem.mr_is_online == hdtas::HDTAS_OC_STATUS::HOCS_OPEN ? true : false);
        obj_temp.insert(PB_AUTO_REPORT_INTERVAL, static_cast<qint64>(elem.pb_ar_int));
        obj_temp.insert(PB_IS_AR, elem.pb_is_ar == 0 ? true : false);
        obj_temp.insert(PB_CAMERA, elem.pb_stu.camera_);
        obj_temp.insert(PB_MICROPHONE, elem.pb_stu.microphone_);
        obj_temp.insert(PB_PRELOAD, elem.pb_stu.preload_);
    }
    json_obj.insert(MR_SUB, obj_temp);
    QJsonDocument json_doc;
    json_doc.setObject(json_obj);
    return json_doc.toJson(QJsonDocument::Compact);
}


// shared variable
static hdtas::HdtasMessage send_msg;
static hdtas::HdtasPackage send_pack;
static std::pair<const unsigned char *, size_t> send_to;
static const char * response_pack = nullptr;
static int cnt = 0;
static build_json build_json_data;


tcp_object::tcp_object(qintptr socketDescriptor, QObject * parent) :
    QObject(parent),
    m_descriptor(socketDescriptor),
    m_tcp_socket_ptr(new QTcpSocket(this))
{

}

tcp_object::~tcp_object() {
    emit stop();
    m_tcp_socket_ptr->close();
    delete m_tcp_socket_ptr;
}

void tcp_object::setupThread(QThread *thread)
{
    connect(thread, SIGNAL(started()), this, SLOT(dowork()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(this, SIGNAL(stop()), thread, SLOT(quit()));
    moveToThread(thread);
}

void tcp_object::dowork() {
    if (!m_tcp_socket_ptr->setSocketDescriptor(m_descriptor)) {
        emit error(m_tcp_socket_ptr->error());
        return ;
    }

    connect(m_tcp_socket_ptr, SIGNAL(disconnected()), this, SLOT(onDisconnected()), Qt::DirectConnection);
    connect(m_tcp_socket_ptr, SIGNAL(readyRead()), this, SLOT(onReadyRead()), Qt::DirectConnection);
}

void tcp_object::onConnected() {

}

void tcp_object::onDisconnected() {
    qDebug() << "tcp disconnected [" << m_tcp_socket_ptr->peerAddress().toString()
             << ":" << m_tcp_socket_ptr->peerPort() << "]";
    m_tcp_socket_ptr->close();

    emit stop();
}

void tcp_object::onReadyRead() {

    QByteArray res;
    res.resize(m_tcp_socket_ptr->bytesAvailable());
    res = m_tcp_socket_ptr->readAll();

   // qDebug() << "recv tcp raw data: " << res;

    hdtas::HdtasPackage package;
    size_t length = 0;
    package.Unpack(reinterpret_cast<const unsigned char *>(res.constData()),
                   static_cast<size_t>(res.size()),
                   length);

    device_mr_id 	mr_id 	= package.GetMMrID();
    h_uint 			msg_id  = package.GetMsgID();
    h_uint			pack_id	= package.GetPackageID();
    h_uint			pack_cnt= package.GetPackageCount();
    QByteArray	 	err_str	= package.GetErrorString();

    hdtas::HdtasMessage message;
    message.Deserialize(&package);
    device_mr_id			mmr_id 	= message.GetMMrID();
    hdtas::HDTAS_MSG_TYPE 	msg_type= message.GetType();
    msg_id	= message.GetMsgID();
    err_str = message.GetErrorString();

    switch (msg_type) {
    case hdtas::HDTAS_MSG_TYPE::HCT_REG_REQ: {
        qDebug() << "reg_request";

        hdtas::HdtasRegRequest reg_req;
        reg_req.Deserialize(&message);
        h_uint status = reg_req.GetStatus();

        hdtas::HdtasRegResponse reg_resp;
        reg_resp.SetMMrID(mr_id);
        reg_resp.SetMsgID(msg_id);
        reg_resp.SetEcode(0);
        hdtas::ispd_date_time date;
        reg_resp.SetDateTime(date);
        reg_resp.StartSerialize();
        cnt = reg_resp.GetSerializeCount();
        while (cnt --) {
            reg_resp.Serialize(&send_msg);
            send_msg.Serialize(&send_pack);
            send_to = send_pack.Pack();
            response_pack = reinterpret_cast<const char *>(send_to.first);

            m_tcp_socket_ptr->write(response_pack, send_to.second);
            m_tcp_socket_ptr->waitForBytesWritten();
        }
    } break;
    case hdtas::HDTAS_MSG_TYPE::HCT_REG_CFM: {
        qDebug() << "reg_confirm";

        // Once received reg confirm type message,
        // send mr & pb request, the pb request should be
        // sent after received mr status info which contains
        // all the mr information

        //request_mr_list_info();
        //request_pb_list_info(mmr_id);

    } break;
    case hdtas::HDTAS_MSG_TYPE::HCT_HB_REQ: {
        qDebug() << "hb_request";
        hdtas::HdtasHeartBeatRequest hb_request;
        hb_request.Deserialize(&message);
        //h_uint status = hb_request.GetStatus();

        hdtas::HdtasHeartBeatResponse hb_response;
        //hb_response.SetEcode(0);
        hb_response.SetMMrID(mr_id);
        hb_response.SetMsgID(msg_id);

        hb_response.StartSerialize();
        cnt = hb_response.GetSerializeCount();
        while (cnt --) {
            hb_response.Serialize(&send_msg);
            send_msg.Serialize(&send_pack);
            send_to = send_pack.Pack();
            response_pack = reinterpret_cast<const char *>(send_to.first);
            m_tcp_socket_ptr->write(response_pack, send_to.second);
            m_tcp_socket_ptr->waitForBytesWritten();
        }
    } break;
    case hdtas::HDTAS_MSG_TYPE::HMT_RD_CFG_REQ: {
        qDebug() << "wr_cfg_requset";

    } break;
    case hdtas::HDTAS_MSG_TYPE::HMT_RD_CFG_RPN: {
        qDebug() << "wr_cfg_response";

    } break;
    case hdtas::HDTAS_MSG_TYPE::HMT_WT_CFG_REQ: {
        qDebug() << "wt_cfg_requset";

    } break;
    case hdtas::HDTAS_MSG_TYPE::HMT_WT_CFG_RPN: {
        qDebug() << "wt_cfg_response";

    } break;
    case hdtas::HDTAS_MSG_TYPE::HMT_CTL_REQ: {
        qDebug() << "ctl_request";


    } break;
    case hdtas::HDTAS_MSG_TYPE::HMT_CTL_RPN: {
        qDebug() << "ctl_response";

        hdtas::HdtasCtlMrPbResponse MrPb_response;
        MrPb_response.Deserialize(&message);

        h_uint err_code 		= MrPb_response.GetEcode();
        h_uint response_id 		= MrPb_response.GetResponseID();
        device_mr_id mmr_id_rep 	= MrPb_response.GetMMrID();
        device_mr_id mr_id_rep 		= MrPb_response.GetMrID();

        build_json_data.mmr_id = mmr_id_rep;

        // parse ctrll response
        QString 		id_str = hdtas::utility::int_2_hex(mmr_id_rep).c_str();
        QJsonDocument 	json_doc;
        QJsonObject 	json_obj;
        json_obj.insert(TYPE, 1);
        json_obj.insert(MMR_ID, id_str);

        hdtas::HDTAS_CTL_TYPE type = MrPb_response.GetResponseType();
        switch (type) {
        case hdtas::HDTAS_CTL_TYPE::HCT_MR_RD_AR_STU: {
            // protocol not implemented
            qDebug() << "read mr ar status";
            hdtas::HDTAS_OC_STATUS status = MrPb_response.GetAutoReportStatus();
            build_json_data.mr_is_ar = status;
            //emit sendMessage();
        } break;
        case hdtas::HDTAS_CTL_TYPE::HCT_MR_RD_AR_ITR: {
            qDebug() << "read mr ar itr";
            h_uint ar_interval = MrPb_response.GetAutoReportInterval();
            json_obj.insert(MR_AUTO_REPORT_INTERVAL, static_cast<int>(ar_interval));
           // json_doc.setObject(json_obj);
           // emit sendMessage(json_doc.toJson(QJsonDocument::Compact));

            build_json_data.mr_ar_int = ar_interval;
        } break;
        case hdtas::HDTAS_CTL_TYPE::HCT_MR_RD_STU_INFO: {
            qDebug() << "read mr status info";
            hdtas::HDTAS_OC_STATUS oc_status = MrPb_response.GetAutoReportStatus();
            h_uint report_interval = MrPb_response.GetAutoReportInterval();
            hdtas::mr_status_array mr_status = MrPb_response.GetStatusInfo();

            // After sending mr request while receive reg confirm message,
            // We can receive mr status information here.
            // for every mr, now we request power board information
            //for (auto elem : mr_status)
            for(unsigned int i = 0; i < mr_status.size(); i++)
            {
                json_obj.insert(MR_ID, hdtas::utility::int_2_hex(mr_status[i].id).c_str());
               // json_obj.insert(MR_STATUS, elem.status == 0 ? "online" : "offline");

              // json_doc.setObject(json_obj);
              //  emit sendMessage(json_doc.toJson(QJsonDocument::Compact));
                request_pb_list_info(mr_status[i].id);

                struct sub_mr sub_mr_temp;
                sub_mr_temp.mr_id = mr_status[i].id;
                sub_mr_temp.mr_is_online = mr_status[i].status;
                build_json_data.mmr_sub.append(sub_mr_temp);
            }

        } break;
        case hdtas::HDTAS_CTL_TYPE::HCT_MR_WT_AR_STU: {
            qDebug() << "write mr ar stu";
        } break;
        case hdtas::HDTAS_CTL_TYPE::HCT_MR_WT_AR_ITR: {
            qDebug() << "write mr ar itr";
        } break;
        case hdtas::HDTAS_CTL_TYPE::HCT_MR_WT_REBOOT: {
            qDebug() << "write mr reboot";
        } break;
        case hdtas::HDTAS_CTL_TYPE::HCT_MR_WT_RESET: {
            qDebug() << "write mr reset";
        } break;

        // power board
        case hdtas::HDTAS_CTL_TYPE::HCT_PB_RD_AR_STU: {
            qDebug() << "read pb ar sta";

            device_mr_id mr_id = MrPb_response.GetMrID();
            device_mr_id mmr_id = MrPb_response.GetMMrID();
            hdtas::HDTAS_OC_STATUS oc_status = MrPb_response.GetAutoReportStatus2();
            json_obj.insert(PB_AUTO_REPORT_STATUS, oc_status == hdtas::HDTAS_OC_STATUS::HOCS_OPEN ? "yes" : "no");

            json_doc.setObject(json_obj);
            emit sendMessage(json_doc.toJson(QJsonDocument::Compact));

            foreach (sub_mr index, build_json_data.mmr_sub) {
                if (mr_id == index.mr_id) {
                    index.pb_is_ar = oc_status;
                }
            }
        } break;
        case hdtas::HDTAS_CTL_TYPE::HCT_PB_RD_AR_ITR: {
            qDebug() << "read pb ar itr";

            device_mr_id mr_id = MrPb_response.GetMrID();
            h_uint pb_interval = MrPb_response.GetAutoReportInterval2();
            json_obj.insert(PB_AUTO_REPORT_INTERVAL, static_cast<qint64>(pb_interval));

            json_doc.setObject(json_obj);
            emit sendMessage(json_doc.toJson(QJsonDocument::Compact));

            foreach (sub_mr index, build_json_data.mmr_sub) {
                if (mr_id == index.mr_id) {
                    index.pb_ar_int = pb_interval;
                }
            }
        } break;
        case hdtas::HDTAS_CTL_TYPE::HCT_PB_RD_STU_INFO: {
            qDebug() << "read pb status info";

            device_mr_id mr_id = MrPb_response.GetMrID();
            hdtas::power_board_status pb_status = MrPb_response.GetStatusInfo2();
            hdtas::power_board_status_group pb_group_status = MrPb_response.GetStatusGroupInfo2();

            foreach (sub_mr index, build_json_data.mmr_sub) {
                if (mr_id == index.mr_id) {
                    index.pb_stu = pb_status;
                    index.pb_stu_group = pb_group_status;
                }
            }

        } break;
        case hdtas::HDTAS_CTL_TYPE::HCT_PB_WT_AR_STU: {
            qDebug() << "write pb ar status";
        } break;
        case hdtas::HDTAS_CTL_TYPE::HCT_PB_WT_AR_ITR: {
            qDebug() << "write pb ar itr";
        } break;
        case hdtas::HDTAS_CTL_TYPE::HCT_PB_WT_OC_CMP: {
            qDebug() << "write pb oc cmp";
        } break;
        case hdtas::HDTAS_CTL_TYPE::HCT_PB_WT_REBOOT: {
            qDebug() << "write pb reboot";
        } break;
        case hdtas::HDTAS_CTL_TYPE::HCT_PB_WT_RESET: {
            qDebug() << "write pb reset";
        } break;

        case hdtas::HDTAS_CTL_TYPE::HCT_UNKNOWN: {
            qInfo() << "unkonwn control type";
        } break;

        }// end switch
    } break;

    case hdtas::HDTAS_MSG_TYPE::HMT_UNKNOWN: {
        qInfo() << "unknow message type";
    } break;

    }// end switch

   // qDebug() << "tcp connected [" << m_tcp_socket_ptr->peerAddress().toString()
             //<< ":" << m_tcp_socket_ptr->peerPort() << "], message(" << res.size() <<  ")[" << res << "]";
    //emit sendMessage(QString(), "tcp signal send: " + res);

}

void tcp_object::onWrite(const char *data, qint16 len)
{
   if (!m_tcp_socket_ptr) {
        qCritical() << "write to tcp socket failed";
        return;
   }

   m_tcp_socket_ptr->write(data, len);
   m_tcp_socket_ptr->waitForBytesWritten();
   request_mr_list_info();
}

void tcp_object::onReadMrStatusInfo() {
    hdtas::HdtasCtlMrPbRequest MrPb_request;
    MrPb_request.ReadStatusInfo();
    hdtas::HdtasMessage message;
    MrPb_request.Serialize(&message);
    hdtas::HdtasPackage package;
    message.Serialize(&package);
    std::pair<const unsigned char *, size_t> send_pkg = package.Pack();
    const char * data = reinterpret_cast<const char *>(send_pkg.first);
    if (!m_tcp_socket_ptr) {
        qDebug() << "tcp socket not initialed";
        m_tcp_socket_ptr->setSocketDescriptor(m_descriptor);
    }

    m_tcp_socket_ptr->write(data, send_pkg.second);
    m_tcp_socket_ptr->waitForBytesWritten();
}

void tcp_object::onReadMrAutoreportInterval() {
    hdtas::HdtasCtlMrPbRequest MrPb_request;
    MrPb_request.ReadAutoReportInterval();
    hdtas::HdtasMessage message;
    MrPb_request.Serialize(&message);
    hdtas::HdtasPackage package;
    message.Serialize(&package);
    std::pair<const unsigned char *, size_t> send_pkg = package.Pack();
    const char * data = reinterpret_cast<const char *>(send_pkg.first);
    if (!m_tcp_socket_ptr) {
        qDebug() << "tcp socket not initialed";
        m_tcp_socket_ptr->setSocketDescriptor(m_descriptor);
    }

    m_tcp_socket_ptr->write(data, send_pkg.second);
    m_tcp_socket_ptr->waitForBytesWritten();
}

void tcp_object::onReadMrAutoreportStatus() {
#if 0
    hdtas::HdtasCtlMrPbRequest MrPb_request;
    MrPb_request.ReadAutoReportStatus();
    hdtas::HdtasMessage message;
    MrPb_request.Serialize(&message);
    hdtas::HdtasPackage package;
    message.Serialize(&package);
    std::pair<const unsigned char *, size_t> send_pkg = package.Pack();
    const char * data = reinterpret_cast<const char *>(send_pkg.first);
    if (!m_tcp_socket_ptr) {
        qDebug() << "tcp socket not initialed";
        m_tcp_socket_ptr->setSocketDescriptor(m_descriptor);
    }

    m_tcp_socket_ptr->write(data, send_pkg.second);
    m_tcp_socket_ptr->waitForBytesWritten();
#endif
    emit sendMessage(build_json_data.toJson());
}

void tcp_object::request_mr_list_info() {
    hdtas::HdtasMessage send_msg;
    hdtas::HdtasPackage send_pack;
    std::pair<const unsigned char *, size_t> send_to;
    const char * response_pack = nullptr;
    int cnt = 0;

    // 1.1 read mr status info
    hdtas::HdtasCtlMrPbRequest mr_request_status;
    mr_request_status.ReadStatusInfo();
    mr_request_status.StartSerialize();
    cnt = mr_request_status.GetSerializeCount();
    while (cnt --) {
        mr_request_status.Serialize(&send_msg);
        send_msg.Serialize(&send_pack);
        send_to = send_pack.Pack();
        response_pack = reinterpret_cast<const char *>(send_to.first);

        m_tcp_socket_ptr->write(response_pack, send_to.second);
        m_tcp_socket_ptr->waitForBytesWritten();
    }
    // 1.2 send mr auto report interval
    hdtas::HdtasCtlMrPbRequest mr_request_ar_interval;
    mr_request_ar_interval.ReadAutoReportInterval();
    mr_request_ar_interval.StartSerialize();
    cnt = mr_request_ar_interval.GetSerializeCount();
    while (cnt --) {
        mr_request_ar_interval.Serialize(&send_msg);
        send_msg.Serialize(&send_pack);
        send_to = send_pack.Pack();
        response_pack = reinterpret_cast<const char *>(send_to.first);

        m_tcp_socket_ptr->write(response_pack, send_to.second);
        m_tcp_socket_ptr->waitForBytesWritten();
    }
#if 0
    // 1.3 send mr auto report status
    // not implemented yet

    hdtas::HdtasCtlMrPbRequest mr_request_ar_status;
    mr_request_ar_status.ReadAutoReportStatus();
    mr_request_ar_status.StartSerialize();
    cnt = mr_request_ar_status.GetSerializeCount();
    while (cnt --) {
        mr_request_ar_status.Serialize(&send_msg);
        send_msg.Serialize(&send_pack);
        send_to = send_pack.Pack();
        response_pack = reinterpret_cast<const char *>(send_to.first);

        m_tcp_socket_ptr->write(response_pack, send_to.second);
        m_tcp_socket_ptr->waitForBytesWritten();
    }
#endif
}

void tcp_object::request_pb_list_info(device_mr_id id)
{
    // 2.1 send pb status
    hdtas::HdtasCtlMrPbRequest hb_request_status;
    hb_request_status.ReadStatusInfo(id);
    hb_request_status.StartSerialize();
    cnt = hb_request_status.GetSerializeCount();
    while (cnt --) {
        hb_request_status.Serialize(&send_msg);
        send_msg.Serialize(&send_pack);
        send_to = send_pack.Pack();
        response_pack = reinterpret_cast<const char *>(send_to.first);

        m_tcp_socket_ptr->write(response_pack, send_to.second);
        m_tcp_socket_ptr->waitForBytesWritten();
    }

    // 2.2 send pb auto report interval
    hdtas::HdtasCtlMrPbRequest hb_request_ar_interval;
    hb_request_ar_interval.ReadAutoReportInterval(id);
    hb_request_ar_interval.StartSerialize();
    cnt = hb_request_ar_interval.GetSerializeCount();
    while (cnt --) {
        hb_request_ar_interval.Serialize(&send_msg);
        send_msg.Serialize(&send_pack);
        send_to = send_pack.Pack();
        response_pack = reinterpret_cast<const char *>(send_to.first);

        m_tcp_socket_ptr->write(response_pack, send_to.second);
        m_tcp_socket_ptr->waitForBytesWritten();
    }

    // 2.3 send pb auto report status
    hdtas::HdtasCtlMrPbRequest hb_request_ar_status;
    hb_request_ar_status.ReadAutoReportStatus(id);
    hb_request_ar_status.StartSerialize();
    cnt = hb_request_ar_status.GetSerializeCount();
    while (cnt --) {
        hb_request_ar_status.Serialize(&send_msg);
        send_msg.Serialize(&send_pack);
        send_to = send_pack.Pack();
        response_pack = reinterpret_cast<const char *>(send_to.first);

        m_tcp_socket_ptr->write(response_pack, send_to.second);
        m_tcp_socket_ptr->waitForBytesWritten();
    }
}
