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

#ifndef INICONFIG_H
#define INICONFIG_H
#include "pch.h"
#include <map>


class INIConfig
{
public:
    INIConfig();
    ~INIConfig();
    
    void init(const string filename);
    string format();
    
    int get_value_i(const string seg, const string name);
    string get_value_s(const string seg, const string name);
    double get_value_d(const string seg, const string name);
    
    typedef map<string, map<string, string> > config_type;
    typedef map<string, string> value_type;
private:
    
    INIConfig(const INIConfig& other);
    INIConfig& operator=(const INIConfig& other);
    bool operator==(const INIConfig& other);
    
    map<string, map<string, string> > _config;
};

#endif // INICONFIG_H
