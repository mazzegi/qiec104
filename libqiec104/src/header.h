#ifndef HEADER_HPP
#define HEADER_HPP

#include <QString>
#include <QDateTime>

namespace QIEC104 {

enum COT
{
    Cot_0_INVALID   = 0,
    Cot_1_PERCYC    = 1,
    Cot_2_BACK      = 2,
    Cot_3_SPONT     = 3,
    Cot_4_INIT      = 4,
    Cot_5_REQ       = 5,
    Cot_6_ACT       = 6,
    Cot_7_ACTCON    = 7,
    Cot_8_DEACT     = 8,
    Cot_9_DEACTCON  = 9,
    Cot_10_ACTTERM  = 10,
    Cot_11_RETREM   = 11,
    Cot_12_RETLOC   = 12,
    Cot_13_FILE     = 13,
    Cot_20_INROGEN  = 20,
    Cot_44_UNKTYPID = 44,
    Cot_45_UNKCOT   = 45,
    Cot_46_UNKCA    = 46,
    Cot_47_UNKIOA   = 47,
    Cot__NEG        = 0x40
};
QString cotToString( COT cot );

class VSQ
{
public:
    typedef enum
    {
        sqSeqSet = 0,
        sqSeqObj = 1
    } SQ;
public:
    VSQ();
    VSQ( quint8 data );
    VSQ( SQ sq, quint8 cnt );

    quint8 data() const;
    SQ sq() const;
    quint8 cnt() const;
    QString toString() const;

private:
    quint8 m_data;
};

class Header
{
public:
    static Header decode(const QByteArray & b);
public:
    Header();
    Header( quint8 type, VSQ vsq, COT cot, quint8 origin, quint16 ca );
    bool isNull() const;
    QByteArray encode() const;

    quint8 type() const;
    VSQ vsq() const;
    COT cot() const;
    quint8 origin() const;
    quint16 ca() const;    
    QString toString() const;

private:
    quint8 m_type;
    VSQ    m_vsq;
    COT    m_cot;
    quint8 m_origin;
    quint16 m_ca;    
};

}

#endif // HEADER_HPP
