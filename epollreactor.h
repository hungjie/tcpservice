/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2014  t2s <qizhao_2001@126.com>
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

#ifndef EPOLLREACTOR_H
#define EPOLLREACTOR_H

#include "handler.h"
#include "tcpserver.h"

class EpollReactor
{
public:
    EpollReactor(TCPServer* server, int buffer_size);
    ~EpollReactor();
    void run();
private:
    
    EpollReactor(const EpollReactor& other);
    EpollReactor& operator=(const EpollReactor& other);
    bool operator==(const EpollReactor& other);
    
    TCPServer* _server;
    int _buffer_size;
    
};

#endif // EPOLLREACTOR_H
