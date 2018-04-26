#ifndef CONFIG_H
#define CONFIG_H

namespace QIEC104{

class Config
{
public:
    static Config * inst();
private:
    Config();
    static Config * s_inst;
public:
    static int ioaSize() ;
private:
    int m_ioaSize;
};

}

#endif // CONFIG_H
