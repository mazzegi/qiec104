#ifndef TYPES_HPP
#define TYPES_HPP

#include <QString>

namespace QIEC104 {

class SIQ
{
public:
    SIQ();
    SIQ( quint8 data );
    SIQ( bool set, bool blc, bool rep, bool top, bool val );
    quint8 data() const;

    bool set() const;
    bool blc() const;
    bool rep() const;
    bool top() const;
    bool val() const;

    QString toString() const;

private:
    quint8 m_data;
};

class QDS
{
public:
    QDS();
    QDS( quint8 data );
    QDS( bool ovf, bool blc, bool rep, bool top, bool val );
    quint8 data() const;

    bool ovf() const;
    bool blc() const;
    bool rep() const;
    bool top() const;
    bool val() const;

    QString toString() const;

private:
    quint8 m_data;
};

class SCO
{
public:
    SCO();
    SCO( quint8 data );
    SCO( bool set, bool shortTime, bool longTime, bool se );
    quint8 data() const;

    bool set() const;
    bool shortTime() const;
    bool longTime() const;
    bool se() const;

    QString toString() const;

private:
    quint8 m_data;
};

class QOI{
public:
    QOI();
    static QOI inro();
    quint8 data() const;

    QString toString() const;
private:
    quint8 m_data;
};

}

#endif // TYPES_HPP
