#ifndef TCP_WORKER_H
#define TCP_WORKER_H

#include <QObject>
#include <QTcpServer>

const quint16 tcp_port = 39527;

class tcp_worker : public QTcpServer
{
    Q_OBJECT

public:
    tcp_worker(QObject * parent = 0);
    virtual ~tcp_worker();

    int init();

protected:
    void incomingConnection(qintptr socketDescriptor) override;

signals:
    void finished();
    // write to mainWindows UI
    void sendTcpMessage(const QString & json);
    void sendTcpMessage(const QString & key, const QString & value);
    void sendTcpMessage(const unsigned char * data, size_t length);

    void readStatusInfo();
    void readMrAutoreportInterval();
    void readMrAutoreportStatus();

    // write to tcp_socket_thread
    void write(const char * data, qint16 length);

public slots:
    // emit sendTcpMessage signal
    void onMessage(const QString & json);
    void onMessage(const QString & key, const QString & value);
    void onMessage(const unsigned char * data, size_t length);
    void onReadMrStatusInfo();
    void onReadMrAutoreportInterval();
    void onReadMrAutoreportStatus();

    // emit write signal
    void onRequest(const char * data, qint16 length);
};

#endif // TCP_WORKER_H
