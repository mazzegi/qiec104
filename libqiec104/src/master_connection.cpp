#include <QDebug>
#include <QTimer>
#include <QTcpSocket>

#include "streamer.h"
#include "master_connection.h"

namespace QIEC104 {

MasterConnection * MasterConnection::start(QObject * parent, const Endpoint & endpoint, Processor *proc){
    QTcpSocket * socket = new QTcpSocket();
    MasterConnection * conn = new MasterConnection(parent, socket, endpoint, proc);
    conn->reconnect();
    return conn;
}

MasterConnection::MasterConnection(QObject * parent, QTcpSocket *socket, const Endpoint &endpoint, Processor * proc)
    : Connection(parent, socket, proc), m_endpoint(endpoint), m_proc(proc), m_socket(socket)
{
    connect(this, &Connection::connected, this, &MasterConnection::onConnected);
    connect(this, &Connection::disconnected, this, &MasterConnection::onDisonnected);    
}

void MasterConnection::reconnect(){
    m_socket->connectToHost(m_endpoint.host(), m_endpoint.port());
}

void MasterConnection::onConnected(){
    reset();
    send( ControlFieldU(ControlFunctionStartDTAct) );
}

void MasterConnection::onDisonnected(){
    qDebug() << "reconnect in 5 secs";
    QTimer::singleShot(5000, [=](){
        this->reconnect();
    });
}


}
