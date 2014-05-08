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

#include <new>
#include "bufferallocator.h"

BufferAllocator::BufferAllocator(void* buf, size_t len):_buf(buf), _head(buf), _len(len) , _rest(len), _next(0)
{

}


void BufferAllocator::reset()
{
        _head = _buf; _rest = _len;
        void* next;
        while (_next)
        {
            next = _next;
            _next = *((void**)_next);
            ::operator delete(next);
        }
        //_next = 0;
}


BufferAllocator::BufferAllocator(const BufferAllocator& other)
{

}

BufferAllocator::~BufferAllocator()
{

}

BufferAllocator& BufferAllocator::operator=(const BufferAllocator& other)
{

}

bool BufferAllocator::operator==(const BufferAllocator& other)
{

}


void* operator new(size_t size, BufferAllocator & b)
{
    size = (size + 3) & 0x7FFFFFFC;
    if (b._rest < size){
        // TODO
        // throw std::bad_alloc();
        void* r = ::operator new(size + sizeof(void*));
        *((void**)r) = b._next;
        b._next = r;
        return (void*)((char*)r +sizeof(void*));
    }
    
    void* r = b._head;
    b._head = (char*) b._head + size;
    b._rest -= size;
    return r;
}
