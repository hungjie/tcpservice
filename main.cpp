#include "pch.h"
#include "tcpserver.h"
#include "handler.h"
#include "iniconfig.h"
#include <auto_ptr.h>

int main(int argc, char **argv) {

    //INIConfig c("config.ini");
    INIConfig& c = Singleton<INIConfig>::instance();
    c.init("config.ini");
    
    string handler = c.get_value_s("[sys]", "handler");
    
    
    TCPServer r(c.get_value_i("[sys]", "port"), HandlerBase::get(handler));
    r.run(c.get_value_i("[sys]", "thread"));
    
    r.wait();

    return 0;
}
