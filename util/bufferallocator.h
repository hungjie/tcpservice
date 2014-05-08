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

#ifndef BUFFERALLOCATOR_H
#define BUFFERALLOCATOR_H
#include <cstddef>

class BufferAllocator
{
public:
    friend void* operator new(size_t size, BufferAllocator& b);
        
    BufferAllocator(void* buf, size_t len);
    ~BufferAllocator();
    
    void reset();
private:    
    BufferAllocator(const BufferAllocator& other);
    BufferAllocator& operator=(const BufferAllocator& other);
    bool operator==(const BufferAllocator& other);
    
    void* _buf;    
    size_t _len; 
    void* _head;
    size_t _rest;
    
    void* _next;
    
};


#endif // BUFFERALLOCATOR_H
