#include <QDebug>
#include <QTimer>

#include "streamer.h"
#include "master_connection_tls.h"

namespace QIEC104 {

MasterConnectionTLS * MasterConnectionTLS::start(QObject * parent, const Endpoint & endpoint, Processor *proc){
    QSslSocket * socket = new QSslSocket();
    MasterConnectionTLS * conn = new MasterConnectionTLS(parent, socket, endpoint, proc);
    conn->reconnect();
    return conn;
}

MasterConnectionTLS::MasterConnectionTLS(QObject * parent, QSslSocket *socket, const Endpoint &endpoint, Processor * proc)
    : Connection(parent, socket, proc), m_endpoint(endpoint), m_proc(proc), m_socket(socket)
{
    connect(this, &Connection::connected, this, &MasterConnectionTLS::onConnected);
    connect(this, &Connection::disconnected, this, &MasterConnectionTLS::onDisonnected);
    connect(socket, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(onSslErrors(QList<QSslError>)));
}

void MasterConnectionTLS::reconnect(){
    m_socket->connectToHostEncrypted(m_endpoint.host().toString(), m_endpoint.port());
}

void MasterConnectionTLS::onConnected(){
    reset();
    send( ControlFieldU(ControlFunctionStartDTAct) );
}

void MasterConnectionTLS::onDisonnected(){
    qDebug() << "reconnect in 5 secs";
    QTimer::singleShot(5000, [=](){
        this->reconnect();
    });
}

void MasterConnectionTLS::onSslErrors(const QList<QSslError> &errors){
    foreach( QSslError err, errors){
        m_proc->error( err.errorString());
    }
}

}
