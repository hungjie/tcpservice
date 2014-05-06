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
#include "../pch.h"
#include "sample_handler.h"

extern "C"{

    int sample_handler_init(void*)
    {
      return 1;
    }

  
int sample_handler_handshake(int sock, char* buf, size_t len)
{
  return 1;
}

int sample_handler_input(int sock, char* buf, size_t len)
{
    int r = read(sock, buf, len);

    if (r > 0) return r;
    if (r == 0) return -1;

    if (errno == EAGAIN || errno == EWOULDBLOCK) {
        len = 0;
        return 0;
    }
    return -1;
}

int sample_handler_output(int sock, const char* buf, size_t len)
{
    return write(sock, buf, len);
}

}