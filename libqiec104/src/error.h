#ifndef ERROR_H
#define ERROR_H

#include <QStringList>

namespace QIEC104{

class Error
{
public:
    Error();
    Error(const QString & err);
public:
    bool isNull() const {return m_stack.isEmpty();}
    QString toString() const;
public:
    Error wrap(const QString & err);
private:
    QStringList m_stack;
};

}

#endif // ERROR_H
