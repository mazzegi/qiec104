#ifndef MESSAGEDEF_H
#define MESSAGEDEF_H

#include "qualifier.h"

#pragma pack(push, 1)

namespace QIEC104 {

struct M001MSPNA1{
    SIQ m_siq;
};

struct M011MMENB1{
    quint16 m_value;
    QDS     m_qds;
};

struct C045CSCNA1{
    SCO m_sco;
};

struct C100CICNA1{
    QOI m_qoi;
};

}

#pragma pack(pop)

#endif // MESSAGEDEF_H
