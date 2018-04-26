#ifndef MESSAGECODEC_H
#define MESSAGECODEC_H

#include <QMap>

#include "processor.h"
#include "messagedef.h"
#include "binary.h"
#include "config.h"

namespace QIEC104 {


class CodecBase{
public:
    virtual void parseAndProcessASDU(const Header & header, const QByteArray & data, Processor * proc) = 0;
};

class CodecRegistry{
public:
    static CodecRegistry * inst();
private:
    CodecRegistry();
    static CodecRegistry * s_inst;
    QMap<quint8, CodecBase*> m_codecs;
    QMap<int, quint8>        m_types;
private:
    template<class TYPE> void addCodec(quint8 typeID);
public:
    static CodecBase * codec(quint8 typeID);
    template<class TYPE> static quint8 typeID(){
        return CodecRegistry::inst()->m_types.value(typeid(TYPE).hash_code(), 0);
    }
};

template <class TYPE>
class Codec : public CodecBase{
public:
    static QByteArray makeASDU(COT cot, quint16 ca, quint32 ioa, const TYPE& inst);
    virtual void parseAndProcessASDU(const Header & header, const QByteArray & data, Processor * proc);
public:
    explicit Codec(quint8 typeID) : m_typeID(typeID){}
private:
    quint8 m_typeID;
};

template <class TYPE>
QByteArray Codec<TYPE>::makeASDU(COT cot, quint16 ca, quint32 ioa, const TYPE& inst){
    BinaryWriter w;
    quint8 typeID = CodecRegistry::typeID<TYPE>();
    Header header = Header(typeID, VSQ(VSQ::sqSeqObj,1), cot, 0, ca);
    w.write( header.encode() );
    w.write(ioa, Config::ioaSize());
    w.write<TYPE>(inst);
    return w.data();
}

template <class TYPE>
void Codec<TYPE>::parseAndProcessASDU(const Header & header, const QByteArray & data, Processor * proc){
    int expectedSize = 0;
    if (header.vsq().sq() == VSQ::sqSeqObj){
        expectedSize = header.vsq().cnt() * (Config::ioaSize() + sizeof(TYPE));
    }else{
        expectedSize = Config::ioaSize() + header.vsq().cnt() * (sizeof(TYPE));
    }
    if ( data.size() != expectedSize ){
        proc->error(QString("data size does not match expected size (%1 != %2)").arg(data.size()).arg(expectedSize));
        return;
    }

    BinaryReader r = BinaryReader(data);
    int ioa = 0;
    if (header.vsq().sq() == VSQ::sqSeqSet){
        ioa = r.readInt( Config::ioaSize() );
    }

    for ( int i = 0; i < header.vsq().cnt(); i++){
        if (header.vsq().sq() == VSQ::sqSeqObj){
            ioa = r.readInt( Config::ioaSize() );
        }
        TYPE inst;
        r.read<TYPE>(&inst);
        if (r.error().isNull()){
            proc->process(header, ioa, inst);
        }
    }
    if (!r.error().isNull()){
        proc->error(r.error().toString());
        return;
    }
}



template<class TYPE>
void CodecRegistry::addCodec(quint8 typeID){
    m_codecs.insert(typeID, new Codec<TYPE>(typeID));
    m_types.insert( typeid(TYPE).hash_code(), typeID );
}


}

#endif // MESSAGECODEC_H
