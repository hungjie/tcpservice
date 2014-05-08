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

#ifndef HANDLER_H
#define HANDLER_H
#include "pch.h"

class HandlerBase{
public:
    typedef HandlerBase* (*create_handler_t)();
    
protected:
    virtual int do_handle_handshake(int sock, char*& buf, size_t len) = 0;
    virtual int do_handle_input(int sock, char*& buf, size_t len) = 0;
    virtual int do_handle_output(int sock, const char* buf, size_t len) = 0;
    
public:
    static HandlerBase* get(const string name);
    void next(HandlerBase* next){_nexthandler = next; }
    
    int handle_handshake(int sock, char*& buf, size_t len) {
        if (len < 1) return len;
        int r = do_handle_handshake(sock, buf, len);
        if (_nexthandler)
            return _nexthandler->handle_handshake(sock, buf, r);
        return r;
    }
    int handle_input(int sock, char*& buf, size_t len) {
        if (len < 1) return len;
        int r = do_handle_input(sock, buf, len);
        if (_nexthandler)
            return _nexthandler->do_handle_input(sock, buf, r);
        return r;
    }
    
    int handle_output(int sock, const char* buf, size_t len) {
        if (len < 1) return len;
        if (_nexthandler)
             len = _nexthandler->handle_output(sock, buf, len);
        return do_handle_output(sock, buf, len);
    }
    

    
private:
    HandlerBase* _nexthandler;
};
#endif // HANDLER_H
