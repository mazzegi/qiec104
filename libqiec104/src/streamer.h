#ifndef CODEC_H
#define CODEC_H

#include <QObject>
#include "protocol.h"
#include "processor.h"

namespace QIEC104{

class Streamer : public QObject{
    Q_OBJECT
public:
    Streamer(QObject * parent, Processor * proc);
signals:    
    void receivedControlFieldI(const ControlFieldI & cf);
    void receivedControlFieldU(const ControlFieldU & cf);
    void receivedControlFieldS(const ControlFieldS & cf);
public:
    void append(const QByteArray & b);
    void reset();
private:
    bool parse();
    void decode(const QByteArray & b);
    void decodeASDU(const QByteArray & asdu);
private:
    QByteArray m_buffer;
    Processor * m_proc;
};


}

#endif // CODEC_H
