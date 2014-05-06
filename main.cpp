#include "pch.h"
#include "tcpserver.h"
#include "handler.h"
#include "iniconfig.h"

HandlerBase* (*create_handler)();


int main(int argc, char **argv) {

    //INIConfig c("config.ini");
    INIConfig& c = Singleton<INIConfig>::instance();
    c.init("config.ini");
    
    string handler = c.get_value_s("[sys]", "handler");
    string filename = "./lib" + handler + ".so";
    void* h = dlopen(filename.c_str(), RTLD_LAZY);
    if (!h){ perror("dl open failed: "); exit(1); }
    
//     string init = handler+ "_init";
//     string handshake = handler + "_handshake";
//     string input = handler + "_input";
//     string output = handler + "_output";
    
//     Handler::handle_init = (handle_init_t) dlsym(h, init.c_str());
//     Handler::handle_handshake = (handle_handshake_t) dlsym(h, handshake.c_str());
//     Handler::handle_input = (handle_input_t) dlsym(h, input.c_str());
//     Handler::handle_output = (handle_output_t) dlsym(h, output.c_str());

    string create_handler_s = "create_" + handler;
    create_handler = (HandlerBase* (*)())dlsym(h, create_handler_s.c_str());
    hb = create_handler();
    if (Handler::handle_init) Handler::handle_init(&c);
    
    
    TCPServer r(c.get_value_i("[sys]", "port"));
    r.run(c.get_value_i("[sys]", "thread"));

    return 0;
}
