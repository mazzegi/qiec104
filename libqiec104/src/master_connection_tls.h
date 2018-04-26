#ifndef MASTER_CONNECTION_TLS_H
#define MASTER_CONNECTION_TLS_H

#include <QObject>
#include <QSslSocket>

#include <libqiec104_global.h>

#include "endpoint.h"
#include "error.h"
#include "processor.h"
#include "connection.h"
#include "messagecodec.h"

namespace QIEC104{

class Streamer;
class LIBQIEC104SHARED_EXPORT MasterConnectionTLS : public Connection{
    Q_OBJECT
public:
    static MasterConnectionTLS * start(QObject * parent, const Endpoint & endpoint, Processor *proc);
private:
    explicit MasterConnectionTLS(QObject * parent, QSslSocket * socket, const Endpoint & endpoint, Processor *proc);
public:
    void reconnect();
protected slots:
    void onConnected();
    void onDisonnected();
    void onSslErrors(const QList<QSslError> &errors);
private:
    Endpoint m_endpoint;
    Processor * m_proc;
    QSslSocket * m_socket;
};

}

#endif // MASTER_CONNECTION_TLS_H
