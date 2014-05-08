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

#include "httpforwarder.h"
#include "../tcpsocket.h"

int HttpForwarder::do_handle_output(int sock, const char* buf, size_t len)
{
    return len;
}

int HttpForwarder::do_handle_input(int sock, char*& buf, size_t len)
{
    TCPSocket forward;
    char buffer[2048];
    buf[len] = 0;

    snprintf(buffer, 2047, "GET /index.php?action=input&name=%d&value=%s HTTP/1.1\r\n"
             //"Connection: keep-alive\r\n"
             "Host: localhost\r\n\r\n", sock, buf);

    size_t size = strlen(buffer);

    if (forward.connect("localhost", 80)) {
        write(forward.sock(), buffer,size);
        read(forward.sock(), buf, len);
        close(forward.sock());
        
        //close(sock); // for test 
        return len;
    }
    return -1;
}


int HttpForwarder::do_handle_handshake(int sock, char*& buf, size_t len)
{
    static TCPSocket forward;
    buf[len] = 0;

    snprintf(buf, len, "GET /index.php?action=new&name=%d HTTP/1.1\r\n"
             //"Connection: keep-alive\r\n"
             "Host: localhost\r\n\r\n", sock);

    size_t size = strlen(buf);

    if (forward.connect("localhost", 80)) {
        write(forward.sock(), buf,size);
        read(forward.sock(), buf, len);
        close(forward.sock());
        return len;
    }
    return -1;
}
