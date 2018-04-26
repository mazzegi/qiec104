#include "error.h"

namespace QIEC104{

Error::Error()
    : m_stack() {

}

Error::Error(const QString & err)
    : m_stack(err) {

}

Error Error::wrap(const QString & err){
    m_stack.append(err);
    return *this;
}

QString Error::toString() const{
    return m_stack.join("|");
}

}
