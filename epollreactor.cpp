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

#include "pch.h"
#include "epollreactor.h"
#include "tcpsocket.h"


EpollReactor::EpollReactor(int sock, handle_handshake_t  handshake, handle_input_t  input, handle_output_t output)
    :_sock(sock), _handle_handshake(handshake), _handle_input(input), _handle_output(output)

{
}

EpollReactor::EpollReactor(const EpollReactor& other)
{

}

EpollReactor::~EpollReactor()
{

}

EpollReactor& EpollReactor::operator=(const EpollReactor& other)
{

}

bool EpollReactor::operator==(const EpollReactor& other)
{

}

void EpollReactor::run(size_t buffer_size = 1024)
{

    epoll_event ev, events[10000];

    int _epf = epoll_create(10000);

    ev.data.fd = _sock;
    ev.events = EPOLLIN;
    epoll_ctl(_epf, EPOLL_CTL_ADD, _sock, &ev);

    if (buffer_size < 1024 || buffer_size > 1024 * 1024 * 100) buffer_size = 1024;
    char* buf = new char[buffer_size];
    size_t len = 0;

    int r = 0;

    int peer;
    sockaddr_in addr;
    socklen_t sock_len;
    TCPSocket sock;

    int loop = 1000;
    while(loop) {
        --loop;
        int n = epoll_wait(_epf, events, 10000, -1);
        if (n > 0) {
            //t = clock();
            for(int i = 0; i < n; ++i) {
                if(events[i].data.fd == _sock) {
                    // process accept

                    peer = accept(_sock, (sockaddr*)&addr, &sock_len);
                    if (peer == -1) {
                        if (errno == EAGAIN || errno == EWOULDBLOCK) {
                            perror ("accept by others");
                            continue;

                        }

                        perror("accept error");
                        return;
                    }

                    //_handle_handshake(peer, buf, buffer_size);
                    r = hb->handle_handshake(peer, buf, buffer_size);
                    if (r == -1){ ::close(peer); continue; }

                    sock.sock(peer);
                    sock.set_noblock();
                    ev.data.fd = peer;
                    ev.events = EPOLLIN;

                    epoll_ctl(_epf, EPOLL_CTL_ADD, sock.sock(), &ev);
                } else {
                    // process client input

                    //r = _handle_input(events[i].data.fd, buf, buffer_size);
                    r = hb->handle_input(events[i].data.fd, buf, buffer_size);

                    if (r == -1) {
                        epoll_ctl(_epf, EPOLL_CTL_DEL, events[i].data.fd, &ev);
                        ::close(events[i].data.fd);
                        continue;
                    }


                }
            }
            //cout << n << "cost: " << clock() -t << endl;
        }
    }
}

