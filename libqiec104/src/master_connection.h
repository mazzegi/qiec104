#ifndef MASTER_CONNECTION_H
#define MASTER_CONNECTION_H

#include <QObject>
#include <QSslSocket>

#include <libqiec104_global.h>

#include "endpoint.h"
#include "error.h"
#include "processor.h"
#include "connection.h"
#include "messagecodec.h"

class QTcpSocket;
namespace QIEC104{

class Streamer;
class LIBQIEC104SHARED_EXPORT MasterConnection : public Connection{
    Q_OBJECT
public:
    static MasterConnection * start(QObject * parent, const Endpoint & endpoint, Processor *proc);    
private:
    explicit MasterConnection(QObject * parent, QTcpSocket * socket, const Endpoint & endpoint, Processor *proc);
public:
    void reconnect();
protected slots:
    void onConnected();
    void onDisonnected();
private:
    Endpoint m_endpoint;
    Processor * m_proc;
    QTcpSocket * m_socket;
};

}

#endif // MASTER_CONNECTION_H
