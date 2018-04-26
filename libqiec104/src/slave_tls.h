#ifndef SLAVE_TLS_H
#define SLAVE_TLS_H

#include <QObject>
#include <QSslSocket>
#include <QTcpServer>
#include <QSslKey>
#include <QSslCertificate>

#include <libqiec104_global.h>

#include "error.h"
#include "endpoint.h"
#include "processor.h"
#include "messagecodec.h"

namespace QIEC104{

class SlaveConnection;
class Streamer;
class LIBQIEC104SHARED_EXPORT SlaveTLS : public QTcpServer{
    Q_OBJECT
public:
    explicit SlaveTLS(QObject * parent, Processor *proc);
    void setupPKI(const QSslKey & prvKey, const QSslCertificate & localCert);
public:
    Error start(const Endpoint & ep);
    void  shutdown();
    void  sendASDU(const QByteArray & asdu);
protected:
    virtual void incomingConnection(qintptr socketDescriptor);
private slots:
    void onEncryptionReady();
    void onDisconnected(QString connID);
    void onSslErrors(const QList<QSslError> &errors);
private:
    Processor * m_proc;
    QMap<QString,SlaveConnection*> m_connections;
    QSslKey m_prvKey;
    QSslCertificate m_localCert;
};

}

#endif // SLAVE_TLS_H
