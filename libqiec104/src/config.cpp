#include "config.h"

namespace QIEC104{

#define CONFIG_DEFAULT_IOA_SIZE 3

Config * Config::s_inst = nullptr;
Config * Config::inst(){
    if ( !s_inst ){
        s_inst = new Config();
    }
    return s_inst;
}

int Config::ioaSize() {
    return inst()->m_ioaSize;
}

//

Config::Config()
    : m_ioaSize(CONFIG_DEFAULT_IOA_SIZE)
{

}


}
