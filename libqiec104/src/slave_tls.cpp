#include "slave_tls.h"
#include "slave_connection.h"

namespace QIEC104 {



SlaveTLS::SlaveTLS(QObject * parent, Processor *proc)
    : QTcpServer(parent), m_proc(proc), m_connections()
{
}

void SlaveTLS::setupPKI(const QSslKey & prvKey, const QSslCertificate & localCert){
    m_prvKey = prvKey;
    m_localCert = localCert;
}

Error SlaveTLS::start(const Endpoint & ep){
    if (!this->listen(ep.host(), ep.port())){
        return Error(this->errorString());
    }
    qDebug() << "slave: start listening on" << ep.toString();
    return Error();
}

void SlaveTLS::shutdown(){
    foreach(SlaveConnection * conn, m_connections){
        conn->deleteLater();
    }
    m_connections.clear();
    this->close();
}

void SlaveTLS::sendASDU(const QByteArray & asdu){
    foreach(SlaveConnection * conn, m_connections){
        conn->sendASDU(asdu);
    }
}

void SlaveTLS::incomingConnection(qintptr socketDescriptor){
    QSslSocket * sslSocket = new QSslSocket(this);
    if (!sslSocket->setSocketDescriptor(socketDescriptor)){
        qCritical() << "failed to set socket-descriptor:" << sslSocket->errorString();
        return;
    }
    qDebug() << "new incomming connection:" << sslSocket->peerAddress() << sslSocket->peerPort();

    connect(sslSocket, &QSslSocket::encrypted, this, &SlaveTLS::onEncryptionReady);
    connect(sslSocket, SIGNAL(sslErrors(QList<QSslError>)), this, SLOT(onSslErrors(QList<QSslError>)));

    sslSocket->setPrivateKey(m_prvKey);
    sslSocket->setLocalCertificate(m_localCert);
    sslSocket->setPeerVerifyMode(QSslSocket::VerifyNone);
    sslSocket->startServerEncryption();
}

void SlaveTLS::onEncryptionReady(){
    QSslSocket * sslSocket = qobject_cast<QSslSocket *>(sender());
    qDebug() << "encryption for socket is ready" << sslSocket->peerAddress() << sslSocket->peerPort();
    SlaveConnection * conn = new SlaveConnection(this, sslSocket, m_proc);
    m_connections.insert( conn->id(), conn );
}

void SlaveTLS::onSslErrors(const QList<QSslError> &errors){
    foreach( QSslError err, errors){
        m_proc->error(err.errorString());
    }
}

void SlaveTLS::onDisconnected(QString connID){
    SlaveConnection * conn = m_connections.value(connID);
    if ( conn ){
        conn->deleteLater();
    }
    m_connections.remove(connID);
}

}
