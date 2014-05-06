/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2014  <copyright holder> <email>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "pch.h"
#include "tcpsocket.h"
#include "handler.h"

#include "tcpserver.h"
#include "epollreactor.h"
#include "iniconfig.h"


static void* f(void* imp) {
    EpollReactor* im = (EpollReactor *)imp;
    INIConfig& c = Singleton<INIConfig>::instance();
    int buffer_size = c.get_value_i("[sys]", "max_body_size");
    im->run(buffer_size);
}

void TCPServer::run(int thread_num)
{
    if (thread_num < 1) {
        EpollReactor imp(_sock, Handler::handle_handshake, Handler::handle_input, Handler::handle_output);
        imp.run(2048);
        return;
    }
    
    pthread_t *threads = new pthread_t[thread_num];
    
    EpollReactor imp(_sock, Handler::handle_handshake, Handler::handle_input, Handler::handle_output);
    for (int i = 0; i < thread_num; ++i){
      pthread_create(&threads[i], 0, f, &imp);
      //imp.run();
      cout << "create thread:" << threads[i] << endl;
    }
    for (int i = 0; i < thread_num; ++i)
      pthread_join(threads[i], 0);
}

TCPServer::TCPServer(int port)
{
    TCPSocket  server;
    server.server(port);
    server.set_noblock();
    _sock = server.sock();
}


TCPServer::TCPServer(const TCPServer& other)
{

}

TCPServer::~TCPServer()
{
    close(_sock);
}

TCPServer& TCPServer::operator=(const TCPServer& other)
{

}

bool TCPServer::operator==(const TCPServer& other)
{

}
