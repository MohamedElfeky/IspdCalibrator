#ifndef TCP_SOCKET_THREAD_H
#define TCP_SOCKET_THREAD_H

#include "../hdtasparser/hdtasparser/header.h"

#include <QThread>
#include <QTcpSocket>
#include <QObject>
#include <QCache>

class tcp_object : public QObject
{
   Q_OBJECT

public:
    explicit tcp_object(qintptr socketDescriptor, QObject * parent = 0);
    virtual ~tcp_object();

    void setupThread(QThread * thread);

signals:
    void stop();
    void error(QTcpSocket::SocketError socketError);
    void sendMessage(const QString & json);
    void sendMessage(const QString & key, const QString & value);
    void sendMessage(const unsigned char * data, size_t len);

public slots:
    void onConnected();
    void onDisconnected();

    // read from tcp socket, then call sendMessage signal
    void onReadyRead();

    // write to tcp socket
    void onWrite(const char * data, qint16 len);

    void onReadMrStatusInfo();
    void onReadMrAutoreportInterval();
    void onReadMrAutoreportStatus();

private slots:
    void dowork();

    void request_mr_list_info();
    void request_pb_list_info(device_mr_id id);

private:
    QTcpSocket * 	m_tcp_socket_ptr;
    qintptr 		m_descriptor;
};

class tcp_socket_thread : public QObject {
Q_OBJECT

public:
    explicit tcp_socket_thread(qintptr socketDescriptor, QObject * parent = 0)
        : QObject(parent)
        , m_descriptor(socketDescriptor)
        , m_thread_ptr(new QThread(this))
        , m_tcp_object_ptr(new tcp_object(m_descriptor))
    {  }

    ~tcp_socket_thread() {
        if (m_thread_ptr->isRunning()) {
            stopThread();
        }
        delete m_thread_ptr;
        delete m_tcp_object_ptr;
    }

    inline tcp_object * get_tcp_object_ptr() { return m_tcp_object_ptr;}
    inline QThread * get_thread_ptr() { return m_thread_ptr;}

    void startThread() {
        m_tcp_object_ptr->setupThread(m_thread_ptr);
        m_thread_ptr->start();
    }

signals:
    void stop();

public slots:
    void stopThread() {
        if (m_thread_ptr->isRunning()) {
            m_thread_ptr->quit();
            m_thread_ptr->wait();
        }
    }

private:
    qintptr 	m_descriptor;
    QThread 	* m_thread_ptr;
    tcp_object 	* m_tcp_object_ptr;
};

#endif // TCP_SOCKET_THREAD_H
