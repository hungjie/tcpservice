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


EpollReactor::EpollReactor(TCPServer* tcpserver, int buffer_size):_server(tcpserver), _buffer_size(buffer_size)

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

void EpollReactor::run()
{

    epoll_event ev, events[10000];

    int _epf = epoll_create(10000);

    int sock = _server->sock();
    ev.data.fd = sock;
    ev.events = EPOLLIN;
    epoll_ctl(_epf, EPOLL_CTL_ADD, sock, &ev);

    if (_buffer_size < 1024 || _buffer_size > 1024 * 1024 * 100) _buffer_size = 1024;
    char* buffer = new char[_buffer_size];
    char* buf;
    size_t len = 0;

    int r = 0;

    int peer;
    sockaddr_in addr;
    socklen_t sock_len;
    TCPSocket peersocket;

    while(1) {
        buf = buffer;
        int n = epoll_wait(_epf, events, 10000, -1);
        if (n > 0) {
            //t = clock();
            for(int i = 0; i < n; ++i) {
                if(events[i].data.fd == sock) {
                    // process accept

                    peer = accept(sock, (sockaddr*)&addr, &sock_len);
                    if (peer == -1) {
                        if (errno == EAGAIN || errno == EWOULDBLOCK) {
                            perror ("accept by others");
                            continue;

                        }

                        perror("accept error");
                        return;
                    }

                    r = _server->handle()->handle_handshake(peer, buf, _buffer_size);
                    if (r == -1){ ::close(peer); continue; }

                    peersocket.sock(peer);
                    peersocket.set_noblock();
                    ev.data.fd = peer;
                    ev.events = EPOLLIN;

                    epoll_ctl(_epf, EPOLL_CTL_ADD, peer, &ev);
                    perror ("epoll_ctr has issue? :");
                    cout << "new socket:" << peer << endl << flush;
                } else {
                    
                    r = _server->handle()->handle_input(events[i].data.fd, buf, _buffer_size);

                    if (r == -1) {
                        epoll_ctl(_epf, EPOLL_CTL_DEL, events[i].data.fd, &ev);
                        ::close(events[i].data.fd);
                        cout << "close socket:" << peer << endl << flush;
                        continue;
                    }


                }
            }
            //cout << n << "cost: " << clock() -t << endl;
        }
    }
}

