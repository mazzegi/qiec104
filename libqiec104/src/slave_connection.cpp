#include "slave_connection.h"
#include "streamer.h"
#include <QTimer>
#include <QUuid>

namespace QIEC104 {


SlaveConnection::SlaveConnection(QObject *parent, QTcpSocket *socket, Processor * proc)
    : Connection(parent, socket, proc), m_proc(proc)
{    
    QTimer * timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=](){
        this->send( ControlFieldU(ControlFunctionTestFrameAct) );
    });
    timer->start(10 * 1000);
}

}
