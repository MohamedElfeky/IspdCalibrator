#include "tcp_worker.h"
#include "tcp_socket_thread.h"

tcp_worker::tcp_worker(QObject * parent) : QTcpServer(parent)
{ }

tcp_worker::~tcp_worker() {
    emit finished();
    this->close();
}

//初始化tcp监听
int tcp_worker::init()
{
    if (!this->listen(QHostAddress::Any, tcp_port))
    {
        qCritical() << "tcp server listening failed";
        return -1;
    }
    qInfo() << "tcp server starts listening port [" << tcp_port << "]";
    return 0;
}

void tcp_worker::incomingConnection(qintptr socketDescriptor)
{
    tcp_socket_thread * thread_ptr = new tcp_socket_thread(socketDescriptor);

    connect(thread_ptr, SIGNAL(stop()), thread_ptr, SLOT(stopThread()));
    connect(this, SIGNAL(finished()), thread_ptr, SLOT(deleteLater()));
    connect(thread_ptr->get_thread_ptr(), SIGNAL(finished()),
            thread_ptr->get_thread_ptr(), SLOT(deleteLater()));

    connect(thread_ptr->get_tcp_object_ptr(), SIGNAL(sendMessage(QString)),
            this, SLOT(onMessage(QString)));
    connect(thread_ptr->get_tcp_object_ptr(), SIGNAL(sendMessage(QString,QString)),
            this, SLOT(onMessage(QString,QString)));
    connect(thread_ptr->get_tcp_object_ptr(), SIGNAL(sendMessage(const unsigned char*,size_t)),
            this, SLOT(onMessage(const unsigned char*,size_t)));

    connect(this, SIGNAL(readStatusInfo()),
            thread_ptr->get_tcp_object_ptr(), SLOT(onReadMrStatusInfo()));
    connect(this, SIGNAL(readMrAutoreportInterval()),
            thread_ptr->get_tcp_object_ptr(), SLOT(onReadMrAutoreportInterval()));
    connect(this, SIGNAL(readMrAutoreportStatus()),
            thread_ptr->get_tcp_object_ptr(), SLOT(onReadMrAutoreportStatus()));

    // write data to socket(endpoint)
    connect(this, SIGNAL(write(const char*,qint16)),
            thread_ptr->get_tcp_object_ptr(), SLOT(onWrite(const char*,qint16)));

    thread_ptr->startThread();
}

void tcp_worker::onRequest(const char *data, qint16 length)
{
    emit this->write(data, length);
}

void tcp_worker::onMessage(const QString &json)
{
    emit sendTcpMessage(json);
}

void tcp_worker::onMessage(const QString & key, const QString &value)
{
    emit sendTcpMessage(key, value);
}

void tcp_worker::onMessage(const unsigned char * data, size_t length)
{
    emit sendTcpMessage(data, length);
}

void tcp_worker::onReadMrStatusInfo()
{
    emit readStatusInfo();
}

void tcp_worker::onReadMrAutoreportInterval()
{
    emit readMrAutoreportInterval();
}

void tcp_worker::onReadMrAutoreportStatus()
{
    emit readMrAutoreportStatus();
}
