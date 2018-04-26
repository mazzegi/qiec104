
#include <QTextStream>
#include "header.h"
#include "binary.h"

namespace QIEC104 {

QString cotToString( COT cot )
{
    QString str;
    switch( cot )
    {
    case Cot_0_INVALID: str = "0_INVALID"; break;
    case Cot_1_PERCYC: str = "1_PERCYC"; break;
    case Cot_2_BACK: str = "2_BACK"; break;
    case Cot_3_SPONT: str = "3_SPONT"; break;
    case Cot_4_INIT: str = "4_INIT"; break;
    case Cot_5_REQ: str = "5_REQ"; break;
    case Cot_6_ACT: str = "6_ACT"; break;
    case Cot_7_ACTCON: str = "7_ACTCON"; break;
    case Cot_8_DEACT: str = "8_DEACT"; break;
    case Cot_9_DEACTCON: str = "9_DEACTCON"; break;
    case Cot_10_ACTTERM: str = "10_ACTTERM"; break;
    case Cot_11_RETREM: str = "11_RETREM"; break;
    case Cot_12_RETLOC: str = "12_RETLOC"; break;
    case Cot_13_FILE: str = "13_FILE"; break;
    case Cot_20_INROGEN: str = "20_INROGEN"; break;
    case Cot_44_UNKTYPID: str = "44_UNKTYPID"; break;
    case Cot_45_UNKCOT: str = "45_UNKCOT"; break;
    case Cot_46_UNKCA: str = "46_UNKCA"; break;
    case Cot_47_UNKIOA: str = "47_UNKIOA"; break;
    case Cot__NEG: str = "NEG"; break;
    default: str = "<unknown>"; break;
    }
    return str;
}

///////////////////////

VSQ::VSQ()
    : VSQ(sqSeqSet, 1)
{

}

VSQ::VSQ( quint8 data )
    : m_data(data)
{

}

VSQ::VSQ( SQ sq, quint8 cnt ){
    m_data = 0;
    m_data |= ( sq << 8 );
    if ( cnt > 127 ) cnt = 127;
    m_data |= cnt;
}

quint8 VSQ::data() const {
    return m_data;
}

VSQ::SQ VSQ::sq() const{
    VSQ::SQ s = sqSeqObj;
    if ( m_data & (1 << 7) ){
        s = sqSeqSet;
    }
    return s;
}

quint8 VSQ::cnt() const {
    return (quint8)(m_data & 0x7f);
}

QString VSQ::toString() const{
    QString s;
    if ( sq() == sqSeqObj ) s.append("seq-obj-");
    else s.append("seq-set-");
    s.append( QString("%1").arg((int)cnt()));
    return s;
}

//////////////////////////////

Header Header::decode(const QByteArray & b){

    quint8 type = b[0];
    VSQ vsq = VSQ(b[1]);
    COT cot = COT(b[2]);
    quint8 origin = b[3];
    quint16 ca = *((quint16*)b.mid(4,2).constData());
    return Header(type, vsq, cot, origin, ca);
}

Header::Header()
    : m_type(0),
      m_vsq(),
      m_cot(Cot_0_INVALID),
      m_origin(0),
      m_ca(0)
{}

Header::Header(quint8 type, VSQ vsq, COT cot, quint8 origin, quint16 ca)
    : m_type(type),
      m_vsq(vsq),
      m_cot(cot),
      m_origin(origin),
      m_ca(ca)
{}

bool Header::isNull() const{
    return (m_type == 0);
}

QByteArray Header::encode() const{
    BinaryWriter w;
    w.write(m_type);
    w.write(m_vsq.data());
    w.write(quint8(m_cot));
    w.write(m_origin);
    w.write(m_ca);

    return w.data();
}

quint8 Header::type() const {
    return m_type;
}

VSQ Header::vsq() const {
    return m_vsq;
}

COT Header::cot() const {
    return m_cot;
}

quint8 Header::origin() const {
    return m_origin;
}

quint16 Header::ca() const {
    return m_ca;
}


QString Header::toString() const{
    QString s;
    QTextStream oss(&s);
    oss << "<ty:" << (int)this->m_type;
    oss << "|vsq:" << VSQ(this->m_vsq).toString();
    oss << "|cot:" << cotToString(this->m_cot);
    oss << "|org:" << (int)this->m_origin;
    oss << "|ca:" << (int)this->m_ca << ">";
    return s;
}

}
