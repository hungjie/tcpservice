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
    im->run();
}

void TCPServer::run(int thread_num)
{
    INIConfig& c = Singleton<INIConfig>::instance();
    int buffer_size = c.get_value_i("[sys]", "max_body_size");
    EpollReactor imp(this, buffer_size);
    
    if (thread_num < 1) {
        imp.run();
        return;
    }
    
    pthread_t thread;
    
    
    for (int i = 0; i < thread_num; ++i){
      pthread_create(&thread, 0, f, &imp);
      _threads.push_back(thread);
    }
    
}

TCPServer::TCPServer(int port, HandlerBase* h):_h(h)
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
