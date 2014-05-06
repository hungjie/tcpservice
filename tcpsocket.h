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

#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include "pch.h"

class TCPSocket
{
public:
    TCPSocket(int fd = 0);
    ~TCPSocket();
    void server(int port);
    void set_noblock();
    void close();
    int sock()const {return _sock;}
    void sock(int sock) {_sock = sock; }
private:
  int _sock;
};

#endif // TCPSOCKET_H
