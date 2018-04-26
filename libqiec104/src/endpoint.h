#ifndef ENDPOINT_H
#define ENDPOINT_H

#include <QString>
#include <QHostAddress>

namespace QIEC104 {

class Endpoint
{
public:
    static Endpoint parse(const QString & s);
public:
    Endpoint();    
    Endpoint(const QHostAddress & host, const quint16 & port);
public:
    QString toString() const {return QString("%1:%2").arg(m_host.toString()).arg(m_port); }
    QHostAddress host() const { return m_host; }
    quint16 port() const { return m_port; }
private:
    QHostAddress m_host;
    quint16 m_port;
};

}

#endif // ENDPOINT_H
