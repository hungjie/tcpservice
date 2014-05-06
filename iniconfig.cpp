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

#include <fstream>
#include <algorithm>
#include <sstream>

#include "iniconfig.h"

template<> INIConfig*
Singleton<INIConfig>::_t = 0;

INIConfig::INIConfig()
{

}

void INIConfig::init(const string filename)
{
  ifstream iff(filename.c_str());
  string s, last_s, tag;
  char buf[1024];
  while (iff >> s){
    if ('#' == s[0]){ iff.getline(buf, 1023); continue; }
    if (s[0] == '[' && s[s.length() -1 ] == ']'){ tag = s; }
    else if (s == "=") {iff >> s;  _config[tag][last_s] = s; }
    else
      last_s.swap(s);
  }
}


string INIConfig::format()
{
  stringstream s;
  
  for(config_type::const_iterator it = _config.begin(); it != _config.end(); ++it){
    s <<  it->first << endl;
    for(value_type::const_iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
      s  << "	" << it2->first << " = " << it2->second << endl;
  }
  return s.str();
}


int INIConfig::get_value_i(const string seg, const string name) {
  if (_config.find(seg) != _config.end() && _config[seg].find(name) != _config[seg].end()) {
    stringstream ss; ss << _config[seg][name];
    int r; ss >> r;
    return r;
  }
  return 0;
  
}
string INIConfig::get_value_s(const string seg, const string name) {
  if (_config.find(seg) != _config.end() && _config[seg].find(name) != _config[seg].end()) {
   return _config[seg][name];
  }
  return "";
}
double INIConfig::get_value_d(const string seg, const string name) {
  if (_config.find(seg) != _config.end() && _config[seg].find(name) != _config[seg].end()) {
    stringstream ss; ss << _config[seg][name];
    double r; ss >> r;
    return r;
  }
  return 0;
}

INIConfig::INIConfig(const INIConfig& other)
{

}

INIConfig::~INIConfig()
{

}

INIConfig& INIConfig::operator=(const INIConfig& other)
{

}

bool INIConfig::operator==(const INIConfig& other)
{

}
