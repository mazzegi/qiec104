#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QByteArray>
#include <QString>

namespace QIEC104 {

typedef char byte;
const byte STARTBYTE = 0x68;

enum ControlFunction{
    ControlFunctionStartINV     = byte(0x00),
    ControlFunctionStartDTAct   = byte(0x07),
    ControlFunctionStartDTCon   = byte(0x0B),
    ControlFunctionStopDTAct    = byte(0x13),
    ControlFunctionStopDTCon    = byte(0x23),
    ControlFunctionTestFrameAct = byte(0x43),
    ControlFunctionTestFrameCon = byte(0x83)
};

inline bool isValidControlFunction(byte b){
    return  (b == byte(ControlFunctionStartDTAct))   ||
            (b == byte(ControlFunctionStartDTCon))   ||
            (b == byte(ControlFunctionStopDTAct))    ||
            (b == byte(ControlFunctionStopDTCon))    ||
            (b == byte(ControlFunctionTestFrameAct)) ||
            (b == byte(ControlFunctionTestFrameCon));
}

inline QString ControlFunctionToString(ControlFunction ctrlFunc){
    switch(ctrlFunc){
    case ControlFunctionStartDTAct:
        return "StartDT-Act";
        break;
    case ControlFunctionStartDTCon:
        return "StartDT-Con";
        break;
    case ControlFunctionStopDTAct:
        return "StopDT-Act";
        break;
    case ControlFunctionStopDTCon:
        return "StopDT-Con";
        break;
    case ControlFunctionTestFrameAct:
        return "TestFrame-Act";
        break;
    case ControlFunctionTestFrameCon:
        return "TestFrame-Con";
        break;
    default:
        break;
    }
    return QString();
}

struct ControlFieldU{
    ControlFunction m_ctrlFunc;

    ControlFieldU() : m_ctrlFunc(ControlFunctionStartINV){}
    ControlFieldU(ControlFunction ctrlFunc) : m_ctrlFunc(ctrlFunc){}

    inline QByteArray encode() const{
        QByteArray b;
        b.append( STARTBYTE );
        b.append( byte(4) );
        b.append( byte(m_ctrlFunc) );
        b.append( byte(0) );
        b.append( byte(0) );
        b.append( byte(0) );
        return b;
    }

    inline QString toString() const{
        return QString("ctrl:%1").arg(ControlFunctionToString(m_ctrlFunc));
    }
};

inline QByteArray makeSeqData(quint16 seq){
    quint16 shifted = seq;
    shifted <<= 1;
    return QByteArray( (const char *)(&shifted), 2 );
}

struct ControlFieldI{
    quint16    m_sendSeq;
    quint16    m_recSeq;
    QByteArray m_asdu;

    ControlFieldI() : m_sendSeq(0), m_recSeq(0), m_asdu() {}
    ControlFieldI(quint16 sendSeq, quint16 recSeq, const QByteArray & asdu) : m_sendSeq(sendSeq), m_recSeq(recSeq), m_asdu(asdu) {}

    inline QByteArray encode() const{
        QByteArray b;
        b.append( STARTBYTE );
        b.append( byte(4 + m_asdu.size()) );
        b.append( makeSeqData(m_sendSeq) );
        b.append( makeSeqData(m_recSeq) );
        b.append( m_asdu );
        return b;
    }

    inline QString toString() const{
        return QString("send:%1, rec:%2, asdu:%3").arg(m_sendSeq).arg(m_recSeq).arg(QString(m_asdu.toHex()));
    }
};

struct ControlFieldS{
    quint16    m_recSeq;

    ControlFieldS() : m_recSeq(0) {}
    ControlFieldS(quint16 recSeq) : m_recSeq(recSeq) {}

    inline QByteArray encode() const{
        QByteArray b;
        b.append( STARTBYTE );
        b.append( byte(4) );
        b.append( byte(1) );
        b.append( byte(0) );
        b.append( makeSeqData(m_recSeq) );
        return b;
    }

    inline QString toString() const{
        return QString("rec:%2").arg(m_recSeq);
    }
};

}

#endif // PROTOCOL_H
