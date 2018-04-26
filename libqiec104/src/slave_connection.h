#ifndef SLAVE_CONNECTION_H
#define SLAVE_CONNECTION_H

#include <QObject>
#include <QSslSocket>

#include "protocol.h"
#include "processor.h"
#include "connection.h"

namespace QIEC104 {

class Streamer;
class SlaveConnection : public Connection
{
    Q_OBJECT
public:
    explicit SlaveConnection(QObject * parent, QTcpSocket * socket, Processor *proc);
private:
    Processor * m_proc;
};

}

#endif // SLAVE_CONNECTION_H
