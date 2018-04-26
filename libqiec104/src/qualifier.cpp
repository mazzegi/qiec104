#include "qualifier.h"
#include <QTextStream>

namespace QIEC104 {


SIQ::SIQ(){
    m_data = 0;
}

SIQ::SIQ( quint8 data ){
    m_data = data;
}

SIQ::SIQ( bool set, bool blc, bool rep, bool top, bool val ){
    m_data = 0;
    m_data |= (set ? (1 << 0) : 0 );
    m_data |= (blc ? (1 << 4) : 0 );
    m_data |= (rep ? (1 << 5) : 0 );
    m_data |= (top ? (1 << 6) : 0 );
    m_data |= (val ? (1 << 7) : 0 );
}

bool SIQ::set() const{
    return (m_data & (1 << 0));
}

bool SIQ::blc() const{
    return (m_data & (1 << 4));
}

bool SIQ::rep() const{
    return (m_data & (1 << 5));
}

bool SIQ::top() const{
    return (m_data & (1 << 6));
}

bool SIQ::val() const{
    return (m_data & (1 << 7));
}

QString SIQ::toString() const{
    QString s;
    QTextStream oss(&s);
    oss << "<";
    oss << "s:" << set();
    oss << "|b:" << blc();
    oss << "|r:" << rep();
    oss << "|t:" << top();
    oss << "|v:" << val();
    oss << ">";
    return s;
}

quint8 SIQ::data() const{
    return m_data;
}

//////////////////////////////////////////////////////////////////////////

QDS::QDS(){
    m_data = 0;
}

QDS::QDS( quint8 data ){
    m_data = data;
}

QDS::QDS( bool ovf, bool blc, bool rep, bool top, bool val ){
    m_data = 0;
    m_data |= (ovf ? (1 << 0) : 0 );
    m_data |= (blc ? (1 << 4) : 0 );
    m_data |= (rep ? (1 << 5) : 0 );
    m_data |= (top ? (1 << 6) : 0 );
    m_data |= (val ? (1 << 7) : 0 );
}

bool QDS::ovf() const{
    return (m_data & (1 << 0));
}

bool QDS::blc() const{
    return (m_data & (1 << 4));
}

bool QDS::rep() const{
    return (m_data & (1 << 5));
}

bool QDS::top() const{
    return (m_data & (1 << 6));
}

bool QDS::val() const{
    return (m_data & (1 << 7));
}

QString QDS::toString() const{
    QString s;
    QTextStream oss(&s);
    oss << "<";
    oss << "o:" << ovf();
    oss << "|b:" << blc();
    oss << "|r:" << rep();
    oss << "|t:" << top();
    oss << "|v:" << val();
    oss << ">";
    return s;
}

quint8 QDS::data() const{
    return m_data;
}

//////////////////////////////////////////////////////////////////////////

SCO::SCO(){
    m_data = 0;
}

SCO::SCO( quint8 data ){
    m_data = data;
}

SCO::SCO( bool set, bool shortTime, bool longTime, bool se ){
    m_data = 0;
    m_data |= (set ? (1 << 0) : 0 );
    //set both bits for permanent
    m_data |= (shortTime ? (1 << 2) : 0);
    m_data |= (longTime ? (1 << 3) : 0);
    m_data |= (se ? (1 << 7) : 0 );
}

bool SCO::set() const{
    return (m_data & (1 << 0));
}

bool SCO::shortTime() const{
    return (m_data & (1 << 2));
}

bool SCO::longTime() const{
    return (m_data & (1 << 3));
}

bool SCO::se() const{
    return (m_data & (1 << 7));
}

QString SCO::toString() const{
    QString s;
    QTextStream oss(&s);
    oss << "<";
    oss << "s:" << set();
    oss << "|st:" << shortTime();
    oss << "|lt:" << longTime();
    oss << "|se:" << se();
    oss << ">";
    return s;
}

quint8 SCO::data() const{
    return m_data;
}

///

QOI::QOI()
    : m_data(0)
{

}

QOI QOI::inro(){
    QOI qoi;
    qoi.m_data = 20;
    return qoi;
}

quint8 QOI::data() const{
    return m_data;
}

QString QOI::toString() const{
    if (m_data == 20){
        return "inro";
    }
    return QString("unknown(%1)").arg(m_data);
}

}
