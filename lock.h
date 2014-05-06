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

#ifndef LOCK_H
#define LOCK_H

#include "pch.h"

class Cond;

class Lock
{
public:
    Lock();
    ~Lock();
    void lock();
    void unlock();
private:
    Lock(const Lock& other);
    Lock& operator=(const Lock& other);
    bool operator==(const Lock& other);
    
    pthread_mutex_t _mutex;
    
    friend class Cond;
   
};

class Cond{
public:
    Cond(Lock& lock):_lock(lock){
      pthread_cond_init(&_cond, 0);
    }
    
    ~Cond(){
      pthread_cond_destroy(&_cond);
      
    }
    
    void wait() {
      pthread_cond_wait(&_cond, &(_lock._mutex));
    }
    
    void signal(){
      pthread_cond_signal(&_cond);
    }
    
    void broadcast(){
      pthread_cond_broadcast(&_cond);
    }
    
private:
    
    Lock& _lock;
    pthread_cond_t _cond;

};

class Guard{
public:
   Guard(Lock& lock):_lock(lock){
     _lock.lock();
  }
  ~Guard(){_lock.unlock(); }
private:
  Lock& _lock;
};

#endif // LOCK_H
