#include "slave.h"
#include "slave_connection.h"

namespace QIEC104 {



Slave::Slave(QObject * parent, Processor *proc)
    : QTcpServer(parent), m_proc(proc), m_connections()
{
    connect(this, &QTcpServer::newConnection, this, &Slave::onNewConnection);
}

Error Slave::start(const Endpoint & ep){
    if (!this->listen(ep.host(), ep.port())){
        return Error(this->errorString());
    }
    qDebug() << "slave: start listening on" << ep.toString();
    return Error();
}

void Slave::shutdown(){
    foreach(SlaveConnection * conn, m_connections){        
        conn->deleteLater();
    }
    m_connections.clear();
    this->close();
}

void Slave::sendASDU(const QByteArray & asdu){
    foreach(SlaveConnection * conn, m_connections){
        conn->sendASDU(asdu);
    }
}

void Slave::onNewConnection(){
    QTcpSocket * socket = nullptr;
    while((socket = this->nextPendingConnection()) != nullptr){
        SlaveConnection * conn = new SlaveConnection(this, socket, m_proc);
        connect( conn, &SlaveConnection::disconnected, this, &Slave::onDisconnected);
        m_connections.insert(conn->id(), conn);
    }
}

void Slave::onDisconnected(QString connID){
    SlaveConnection * conn = m_connections.value(connID);
    if ( conn ){
        conn->deleteLater();
    }
    m_connections.remove(connID);
}

}
