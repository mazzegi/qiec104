
#include "streamer.h"
#include "binary.h"
#include "messagecodec.h"

namespace QIEC104{

Streamer::Streamer(QObject * parent, Processor * proc)
    : QObject(parent),
      m_buffer(),
      m_proc(proc) {}

void Streamer::append(const QByteArray & b){
    m_buffer.append(b);
    while (parse()){}
}

void Streamer::reset(){
    m_buffer.clear();
}

bool Streamer::parse(){
    //find start of stream and purge leading bytes
    int startIdx = m_buffer.indexOf(STARTBYTE);
    if (startIdx < 0){
        m_buffer.clear();
        return false;
    }
    m_buffer.remove(0, startIdx);

    if( m_buffer.size() < 2){
        // need more
        return false;
    }
    int len = m_buffer[1];
    if (m_buffer.size() < (2 + len)){
        // need more
        return false;
    }
    QByteArray token = m_buffer.mid(2, 2 + len);
    m_buffer.remove(0, 2 + len);
    decode(token);
    return true;
}


void Streamer::decode(const QByteArray & b){
    bool b1 = ((b[0]&1)==1);
    bool b2 = ((b[0]&2)==2);
    if (!b1){
        BinaryReader r(b);
        quint16 sendSeq = r.readInt(2);
        quint16 recSeq = r.readInt(2);
        QByteArray asdu = r.readByteArray();
        if (r.error().isNull()){
            emit receivedControlFieldI( ControlFieldI(sendSeq, recSeq, asdu) );
            decodeASDU(asdu);
        }
    }else if (b2){
        if (b[0] == 1){
            BinaryReader r(b);
            r.readInt(2);
            quint16 recSeq = r.readInt(2);
            if (r.error().isNull()){
                emit receivedControlFieldS( ControlFieldS(recSeq) );
            }
        }else{
            byte ctrlFunc = b[0];
            if (isValidControlFunction(ctrlFunc)){
                emit receivedControlFieldU( ControlFieldU(ControlFunction(ctrlFunc)) );
            }
        }
    }
}

void Streamer::decodeASDU(const QByteArray & asdu){
    if (asdu.size() < 6){
        return;
    }
    QByteArray bHeader = asdu.left(6);
    QByteArray bData = asdu.mid(6);
    Header h = Header::decode(bHeader);
    if (h.isNull()){
        return;
    }

    CodecBase * codec = CodecRegistry::codec(h.type());
    if(codec){
        codec->parseAndProcessASDU(h, bData, m_proc);
    }
}

}
