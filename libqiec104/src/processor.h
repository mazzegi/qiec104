#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "messagedef.h"
#include "header.h"

namespace QIEC104 {

class Processor{
public:
    virtual void error(const QString &){}
public:
    virtual void process(const Header &, quint32 /*ioa*/, const M001MSPNA1 &){}
    virtual void process(const Header &, quint32 /*ioa*/, const M011MMENB1 &){}
    virtual void process(const Header &, quint32 /*ioa*/, const C045CSCNA1 &){}
    virtual void process(const Header &, quint32 /*ioa*/, const C100CICNA1 &){}
};

}

#endif // PROCESSOR_H
