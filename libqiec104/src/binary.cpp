#include "binary.h"

namespace QIEC104{

BinaryReader::BinaryReader(const QByteArray & data)
    : m_data(data), m_pos(0), m_err(){}

int BinaryReader::readInt(int len){
    if((m_pos + len) > m_data.size()){        
        m_err.wrap("index out of bounds");
        return 0;
    }
    int v = 0;
    memcpy(&v, m_data.mid(m_pos, len).constData(), len);
    m_pos += len;
    return v;
}

quint8 BinaryReader::readByte(){
    if((m_pos + 1) > m_data.size()){        
        m_err.wrap("index out of bounds");
        return 0;
    }
    quint8 v = m_data[m_pos];
    m_pos += 1;
    return v;
}

QByteArray BinaryReader::readByteArray(int len){
    if (len==-1){
        QByteArray b = m_data.mid(m_pos);
        m_pos = m_data.size()-1;
        return b;
    }else if ((m_pos + len) > m_data.size()){
        m_err.wrap("index out of bounds");
        return QByteArray();
    }
    QByteArray b = m_data.mid(m_pos, len);
    m_pos += len;
    return b;
}

//
BinaryWriter::BinaryWriter()
    : m_data(), m_err()
{

}

void BinaryWriter::write(int val, int len){
    m_data.append((const char *)(&val), len);
}

void BinaryWriter::write(quint16 val){
    write(val, sizeof(val));
}

void BinaryWriter::write(quint8 byte){
    m_data.append((char)byte);
}

void BinaryWriter::write(const QByteArray & b){
    m_data.append(b);
}

}
