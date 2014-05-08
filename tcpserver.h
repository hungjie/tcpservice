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

#ifndef REACTOR_H
#define REACTOR_H

#include "pch.h"
#include <vector>
#include "handler.h"

class TCPServer
{
public:
    TCPServer(int port, HandlerBase* h);
    ~TCPServer();
    void run(int thread_num = 1);
    int sock() {return _sock;}
    HandlerBase* handle(){return _h;}
    
    void wait(){
        for (vector<pthread_t>::iterator it = _threads.begin(); it != _threads.end(); ++it)
            pthread_join(*it, 0);
    }
    
private:
    TCPServer(const TCPServer& other);
    TCPServer& operator=(const TCPServer& other);
    bool operator==(const TCPServer& other);
private:
  int _sock;
  HandlerBase *_h;
  vector<pthread_t> _threads;
  
};

#endif // REACTOR_H
