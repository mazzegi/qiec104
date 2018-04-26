#include "connection.h"
#include "streamer.h"
#include <QSslSocket>

#include <QUuid>

namespace QIEC104 {

Connection::Connection(QObject *parent, QTcpSocket *socket, Processor *proc)
    : QObject(parent),
      m_socket(socket),
      m_proc(proc),
      m_sendSeq(0),
      m_recSeq(0)
{
    m_id = QUuid::createUuid().toString();
    m_streamer = new Streamer(this, proc);

    connect(m_socket, &QAbstractSocket::stateChanged, this, &Connection::onStateChanged);
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));
    connect(m_socket, &QAbstractSocket::readyRead, this, &Connection::onReadyRead);

    connect(m_streamer, &Streamer::receivedControlFieldI, this, &Connection::onControlFieldI);
    connect(m_streamer, &Streamer::receivedControlFieldU, this, &Connection::onControlFieldU);
    connect(m_streamer, &Streamer::receivedControlFieldS, this, &Connection::onControlFieldS);
}

Connection::~Connection(){
    m_socket->deleteLater();
    m_socket = nullptr;
}

void Connection::reset(){
    m_sendSeq = 0;
    m_recSeq = 0;
    m_streamer->reset();
}

void Connection::onStateChanged(QAbstractSocket::SocketState socketState){
    switch(socketState){
    case QAbstractSocket::ConnectedState:
        qDebug() << "connected";
        emit connected(m_id);
        break;
    case QAbstractSocket::UnconnectedState:
        qDebug() << "disconnected - " << m_socket->errorString();
        emit disconnected(m_id);
        break;
    default:
        break;
    }
}

void Connection::onSocketError(QAbstractSocket::SocketError /*err*/){
    m_proc->error(m_socket->errorString());
}

void Connection::onReadyRead(){
    m_streamer->append(m_socket->readAll());
}

void Connection::send(const ControlFieldI & cf){
    if ( m_socket->state() == QAbstractSocket::ConnectedState){
        qDebug() << "send I-Frame:" << cf.toString();
        m_socket->write(cf.encode());
        m_sendSeq++;
    }
}

void Connection::send(const ControlFieldU & cf){
    if ( m_socket->state() == QAbstractSocket::ConnectedState){
        qDebug() << "send U-Frame:" << cf.toString();
        m_socket->write(cf.encode());
    }
}

void Connection::send(const ControlFieldS & cf){
    if ( m_socket->state() == QAbstractSocket::ConnectedState){
        qDebug() << "send S-Frame:" << cf.toString();
        m_socket->write(cf.encode());
    }
}

void Connection::sendASDU(const QByteArray & asdu){
    send( ControlFieldI(m_sendSeq, m_recSeq, asdu ) );
}

void Connection::onControlFieldI(const ControlFieldI & cf){
    qDebug() << "rec. I-Frame:" << cf.toString();
    m_recSeq++;
    send( ControlFieldS(m_recSeq) );
}

void Connection::onControlFieldS(const ControlFieldS & cf){
    qDebug() << "rec. S-Frame:" << cf.toString();
}

void Connection::onControlFieldU(const ControlFieldU & cf){
    qDebug() << "rec. U-Frame:" << cf.toString();
    switch(cf.m_ctrlFunc){
    case ControlFunctionTestFrameAct:
        send( ControlFieldU(ControlFunctionTestFrameCon) );
        break;
    case ControlFunctionStartDTAct:
        send( ControlFieldU(ControlFunctionStartDTCon) );
        break;
    case ControlFunctionStopDTAct:
        send( ControlFieldU(ControlFunctionStopDTCon) );
        break;
    default:
        break;
    }
}

}
