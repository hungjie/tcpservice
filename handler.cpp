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

#include <map>
#include "handler.h"
#include "iniconfig.h"

HandlerBase* HandlerBase::get(const string name)
{
    static map<string, HandlerBase* > handlers;
    if (handlers.find(name) != handlers.end()) return handlers[name];
    
    string filename = "./lib" + name + ".so";
    void* h = dlopen(filename.c_str(), RTLD_LAZY);
    if (!h){ perror("dl open failed: "); exit(1); }
    

    string create_handler_s = "create_" + name;
    HandlerBase::create_handler_t create_handler = (HandlerBase::create_handler_t)dlsym(h, create_handler_s.c_str());
    
    HandlerBase* hb;
    handlers[name] = hb = create_handler();
    
    INIConfig& c = Singleton<INIConfig>::instance();

    string next = c.get_value_s("[" + name + "]", "next");
    if (next != ""){
        HandlerBase* next_handler = HandlerBase::get(next);
        hb->next(next_handler);
    }
    
    return hb; 
}

