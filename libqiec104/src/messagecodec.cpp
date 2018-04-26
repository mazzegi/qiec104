#include "messagecodec.h"

namespace QIEC104 {

CodecRegistry * CodecRegistry::s_inst = nullptr;

CodecRegistry * CodecRegistry::inst(){
    if(!s_inst){
        s_inst = new CodecRegistry();
    }
    return s_inst;
}

CodecBase * CodecRegistry::codec(quint8 typeID){
    return CodecRegistry::inst()->m_codecs.value(typeID, nullptr);
}

CodecRegistry::CodecRegistry()
    : m_codecs(),
      m_types()
{
    addCodec<M001MSPNA1>(1);
    addCodec<M011MMENB1>(11);
    addCodec<C045CSCNA1>(45);
    addCodec<C100CICNA1>(100);
}

}
