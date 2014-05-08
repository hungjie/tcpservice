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

#ifndef HTTPFORWARDER_H
#define HTTPFORWARDER_H

#include "../handler.h"

class HttpForwarder : public HandlerBase
{
protected:
    virtual int do_handle_output(int sock, const char* buf, size_t len);
    virtual int do_handle_input(int sock, char*& buf, size_t len);
    virtual int do_handle_handshake(int sock, char*& buf, size_t len);
};

extern "C" HandlerBase* create_httpforwarder(){

    new HttpForwarder();
}

#endif // HTTPFORWARDER_H