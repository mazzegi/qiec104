#include <QCoreApplication>
#include <QDebug>
#include <QTimer>
#include <QByteArray>

#include <libqiec104.h>

using namespace QIEC104;


QString timestamp(){
    return QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
}

class MyProcessor : public QIEC104::Processor{
public:
    virtual void error(const QString & err){
        qWarning() << timestamp() << "error:" << err;
    }

    virtual void process(const QIEC104::Header & header, quint32 ioa, const QIEC104::M001MSPNA1 & msg){
        qDebug() << timestamp() <<  "codec-process: " << header.toString() << ioa << msg.m_siq.toString();
    }

    virtual void process(const QIEC104::Header & header, quint32 ioa, const QIEC104::M011MMENB1 & msg){
        qDebug() << timestamp() <<  "codec-process: " << header.toString() << ioa << msg.m_value << msg.m_qds.toString();
    }

    virtual void process(const QIEC104::Header & header, quint32 ioa, const QIEC104::C045CSCNA1 & msg){
        qDebug() << timestamp() <<  "codec-process: " << header.toString() << ioa << msg.m_sco.toString();
    }

    virtual void process(const QIEC104::Header & header, quint32 ioa, const QIEC104::C100CICNA1 & msg){
        qDebug() << timestamp() <<  "codec-process: " << header.toString() << ioa << msg.m_qoi.toString();
    }
};

bool g_value = true;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Slave * slave = new Slave(nullptr, new MyProcessor());
    Error err = slave->start( Endpoint::parse(":2701") );
    if (!err.isNull()){
        qCritical() << "error:" << err.toString();
        return 1;
    }

    QTimer * timer = new QTimer(0);
    QObject::connect(timer, &QTimer::timeout, [=](){
        qDebug() << timestamp() << "toggle message";
        M001MSPNA1 msg;
        msg.m_siq = SIQ(g_value, false, false, false, false);
        slave->sendASDU( Codec<M001MSPNA1>::makeASDU(Cot_3_SPONT, 11, 41, msg) );
        g_value = !g_value;
    });
    timer->start(5000);

    return a.exec();
}
