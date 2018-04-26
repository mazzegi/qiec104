#include <QStringList>

#include "endpoint.h"

namespace QIEC104 {

Endpoint Endpoint::parse(const QString & s){
    QStringList list = s.split(":", QString::KeepEmptyParts);
    if (list.size() != 2 ){
        return Endpoint();
    }
    if (list.at(0).isEmpty()){
        return Endpoint(QHostAddress::Any, list.at(1).toUShort());
    }
    return Endpoint( QHostAddress(list.at(0)), list.at(1).toUShort());
}

Endpoint::Endpoint()
    : m_host(), m_port(0) {

}

Endpoint::Endpoint(const QHostAddress &host, const quint16 & port)
    : m_host(host), m_port(port) {

}

}
