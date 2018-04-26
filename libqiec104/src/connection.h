#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QTcpSocket>

#include "protocol.h"
#include "endpoint.h"

namespace QIEC104 {

class Streamer;
class Processor;
class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(QObject * parent, QTcpSocket * socket, Processor *proc);
    virtual ~Connection();
public:    
    void sendASDU(const QByteArray & asdu);
    void reset();    
    QString id() const {return m_id;}    
signals:
    void connected(QString connID);
    void disconnected(QString connID);
private slots:
    void onStateChanged(QAbstractSocket::SocketState socketState);
    void onSocketError(QAbstractSocket::SocketError);
    void onReadyRead();
    void onControlFieldI(const ControlFieldI & cf);
    void onControlFieldU(const ControlFieldU & cf);
    void onControlFieldS(const ControlFieldS & cf);
protected:
    void send(const ControlFieldI & cf);
    void send(const ControlFieldU & cf);
    void send(const ControlFieldS & cf);
private:
    QTcpSocket * m_socket;
    Processor * m_proc;
    QString m_id;
    Streamer * m_streamer;
    quint16 m_sendSeq;
    quint16 m_recSeq;
};

}

#endif // CONNECTION_H
