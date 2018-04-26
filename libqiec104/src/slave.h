#ifndef SLAVE_H
#define SLAVE_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>

#include <libqiec104_global.h>

#include "error.h"
#include "endpoint.h"
#include "processor.h"
#include "messagecodec.h"

namespace QIEC104{

class SlaveConnection;
class Streamer;
class LIBQIEC104SHARED_EXPORT Slave : public QTcpServer{
    Q_OBJECT
public:
    explicit Slave(QObject * parent, Processor *proc);
public:
    Error start(const Endpoint & ep);
    void  shutdown();
    void  sendASDU(const QByteArray & asdu);
private slots:
    void onNewConnection();
    void onDisconnected(QString connID);
private:
    Processor * m_proc;
    QMap<QString,SlaveConnection*> m_connections;
};

}

#endif // SLAVE_H
