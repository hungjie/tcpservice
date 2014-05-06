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

extern "C" {
  typedef int (*handle_init_t)(void*);
  typedef int (*handle_handshake_t)(int sock, char* buf, size_t len);
  typedef int (*handle_input_t)(int sock, char* buf, size_t len);
  typedef int (*handle_output_t)(int sock, const char* buf, size_t len);  
};

class Handler{
public:
  static handle_init_t handle_init;
  static handle_handshake_t handle_handshake;
  static handle_input_t handle_input;
  static handle_output_t handle_output;
  
};

class HandlerBase{
public:
    virtual int handle_handshake(int sock, char* buf, size_t len) = 0;
    virtual int handle_input(int sock, char* buf, size_t len) = 0;
    virtual int handle_output(int sock, const char* buf, size_t len) = 0;
};

extern HandlerBase *hb;

#endif // HANDLER_H
