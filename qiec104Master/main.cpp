#include <QCoreApplication>
#include <QDebug>
#include <QTimer>
#include <QByteArray>

#include <libqiec104.h>

QString timestamp(){
    return QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz");
}

using namespace QIEC104;

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
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MasterConnection * master = MasterConnection::start(0, Endpoint(QHostAddress::LocalHost, 2701), new MyProcessor());

//    QIEC104::MasterConnection * master = new QIEC104::MasterConnection(0, QIEC104::Endpoint(QHostAddress::LocalHost, 2701), new MyProcessor());
//    master->reconnect();

    qDebug() << "start main loop";    
    QTimer::singleShot(5000, [=](){
        qDebug() << timestamp() << "send inro";
        QIEC104::C100CICNA1 cmd;
        cmd.m_qoi = QIEC104::QOI::inro();
        master->sendASDU( QIEC104::Codec<QIEC104::C100CICNA1>::makeASDU(QIEC104::Cot_6_ACT, 22, 0, cmd ) );
    });

    QTimer::singleShot(8000, [=](){
        qDebug() << timestamp() << "send cmd";
        QIEC104::C045CSCNA1 cmd;
        cmd.m_sco = QIEC104::SCO(true, true, true, true);
        master->sendASDU( QIEC104::Codec<QIEC104::C045CSCNA1>::makeASDU(QIEC104::Cot_6_ACT, 22, 43, cmd ) );
    });

    a.exec();
}


