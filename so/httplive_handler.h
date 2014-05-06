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

#ifndef HTTPLIVE_HANDLER_H
#define HTTPLIVE_HANDLER_H

extern "C"
{
  int httplive_handler_init(void*);
  int httplive_handler_handshake(int sock, char* buf, size_t len);
  int httplive_handler_input(int sock, char* buf, size_t len);
  int httplive_handler_output(int sock, const char* buf, size_t len);
};



#endif // HTTPLIVE_HANDLER_H
