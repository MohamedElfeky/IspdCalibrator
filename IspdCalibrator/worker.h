#ifndef WORKER_H
#define WORKER_H
#include "../hdtasparser/hdtasparser/hdtasparser.h"
#include "../hdtasparser/hdtasparser/utility.h"

#include <QObject>
#include <QUdpSocket>

class QThread;
class QUdpSocket;

const quint16 udp_port = 39527;

class Worker : public QObject
{
    Q_OBJECT
public:
    explicit Worker(QObject *parent = 0);
    virtual ~Worker();

    void setupWorker(QThread * thread);

signals:

public slots:
    virtual void dowork() = 0;
    virtual void handle_connections() = 0;
};

// udp
class udp_worker : public Worker {
    Q_OBJECT

public:
    explicit udp_worker(QObject * parent = 0);
    virtual ~udp_worker();

protected:
    void dowork() override;
    void handle_connections() override;

signals:
    void sendUdpMessage(const QString & msg);

public slots:
    // It is not necesary to detect the udp client disconnecting
    ///void onDisconnect();

private:
   QUdpSocket * m_udp_socket_ptr;
};


// serialport udp
class serialport_udp_worker : public Worker{
    Q_OBJECT

public:
    explicit serialport_udp_worker(QObject * parent = 0);
    virtual ~serialport_udp_worker();

signals:
    void sendUdpMessage(const QString & msg);
    void sendUdpLogMessage(QString log_str);
    void sendUdpDefaultMsg(QString def_log_str);
    void sendUdpData(QString upd_data);

protected:
    void dowork() override;
    void handle_connections() override;
private:
    QUdpSocket * m_udp_socket_ptr;
};

#endif // WORKER_H
