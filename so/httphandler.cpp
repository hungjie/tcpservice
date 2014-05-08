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

#include "httphandler.h"

int HttpHandler::do_handle_output(int sock, const char* buf, size_t len)
{
  return write(sock, buf, len);
}

int HttpHandler::do_handle_input(int sock, char*& buf, size_t len)
{
  int r = read(sock, buf, len);

        if (r > 0)  {
            const char* http_response =
                "HTTP/1.1 200 OK\r\n"
                "Connection: Keep-Alive\r\n"
                "Content-Type: text/html; charset=utf-8\r\n"
                "Content-Length: 7\r\n"
                "\r\n"
                "TEST OK";
            int http_response_l = strlen(http_response);
            int write_len = 0;
	    
	    clock_t c = clock() ;
            for(int i = 0; i < 1000000; ++i);
	     printf("input cost: %.10f\n", (clock() - c) * 1.0 / CLOCKS_PER_SEC);

            handle_output(sock, http_response, http_response_l);

            return r;
        }
        /*{
          buf[r] = 0;
          return r;
        }//*/

        if (r == 0) return -1;

        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            return 0;
        }
        return -1;
}

int HttpHandler::do_handle_handshake(int sock, char*& buf, size_t len)
{
  return 1;
}
