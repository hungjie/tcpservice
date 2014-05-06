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

#include "tcpsocket.h"

TCPSocket::TCPSocket(int fd):_sock(fd)
{

}


TCPSocket::~TCPSocket()
{

}

void TCPSocket::server(int port)
{
    _sock = socket(AF_INET, SOCK_STREAM, 0);
    if(_sock == -1) {
        perror("socket: ");
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);

    if (-1 == bind(_sock, (sockaddr*)(&server_addr), sizeof(server_addr))){
      perror("bind: ");
    }

    listen(_sock, 20000);

}

void TCPSocket::set_noblock()
{
    int flag = fcntl(_sock, F_GETFL);
    flag |= O_NONBLOCK;
    fcntl(_sock, F_SETFL, flag);
}

void TCPSocket::close()
{
    ::close(_sock);
}
