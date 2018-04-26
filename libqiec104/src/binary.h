#ifndef BINARY_H
#define BINARY_H

#include <QByteArray>
#include "error.h"

namespace QIEC104{

class BinaryReader
{
public:
    BinaryReader(const QByteArray & data);
public:
    Error error() const {return m_err;}
public:
    int        readInt(int len);
    quint8     readByte();
    QByteArray readByteArray(int len = -1);
    template<class TYPE> void read(TYPE * v){
        int len = sizeof(TYPE);
        if ((m_pos + len) > m_data.size()){
            m_err.wrap("index out of bounds");
            return;
        }
        memcpy(v, m_data.mid(m_pos, len).constData(), len);
        m_pos += len;
    }
private:
    QByteArray m_data;
    int m_pos;
    Error m_err;
};

class BinaryWriter{
public:
    BinaryWriter();
public:
    Error error() const {return m_err;}
    QByteArray data() const {return m_data;}
public:
    void write(int val, int len);
    void write(quint16 val);
    void write(quint8 byte);
    void write(const QByteArray & b);
    template<class TYPE> void write(const TYPE & v){
        write( QByteArray((const char *)(&v), sizeof(TYPE) ) );
    }
private:
    QByteArray m_data;
    Error m_err;
};

}

#endif // BINARY_H
