#ifndef TIME_HPP
#define TIME_HPP

#include <QDateTime>

namespace QIEC104 {

inline QDateTime qDateTimeFromCP56Time(const QByteArray & data){
    if ( data.size() < 7){
        return QDateTime();
    }
    quint16 msec  = ( (data[0] ) | ( data[1] << 8 ) );
    quint8  mins  = ( data[2] & 0x3F );
    quint8  hours = ( data[3] & 0x1F );
    //quint8  dow   = ( ( data[4] >> 5 ) & 0x07 );
    quint8  dom   = ( ( data[4] ) & 0x1F );
    quint8  month = ( data[5] & 0x0F );
    quint8  yy    = ( data[6] & 0x7F );
    quint16 sec   = msec / 1000;

    return QDateTime(QDate(2000+yy, month, dom), QTime(hours, mins, sec, msec - sec * 1000 ));
}

inline QByteArray CP56TimeFromQDateTime(const QDateTime & dt){
    QByteArray data(7, 0);
    uint16_t msec = dt.time().second() * 1000 + dt.time().msec();

    data[0] = msec;
    data[1] = msec >> 8;
    data[2] = (uint8_t)dt.time().minute() & 0x3F;
    data[3] = (uint8_t)dt.time().hour() & 0x1F;
    data[4] = (uint8_t)dt.date().dayOfWeek() << 5;
    data[4] = data[4] | (uint8_t)dt.date().day();
    data[5] = (uint8_t)dt.date().month() & 0x0F;
    data[6] = (uint8_t)(dt.date().year() - 2000) & 0x7F;

    return data;
}

}

#endif // TIME_HPP
