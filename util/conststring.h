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

#ifndef CONSTSTRING_H
#define CONSTSTRING_H

#include <cstring>

namespace Util {

using namespace std;

class ConstString
{
public:
    ConstString(const char* str, int len): _str(str), _len(len) {}
    ConstString(const char* str = 0):_str(str) {
        if (str == 0) _len = 0;
        _len  = strlen(str);
    }
    operator const char*() const {
        return _str;
    }
    bool operator < (const ConstString& other) const
    {
        int b = strncmp(_str, other._str, _len);
        if (b < 0 || (b == 0 && _len < other._len)) return true;
        return false;
    }

    bool operator < (const char* s) const
    {
        int b = strncmp(_str, s, _len);
        if (b < 0 || (b == 0 && _len < strlen(s))) return true;
        return false;
    }

    bool operator == (const ConstString& other) const
    {
        if (_str == other._str) return true;
        if (_len != other._len) return false;
        return strncmp(_str, other._str, _len) == 0;
    }

    bool operator == (const char* s) const
    {
        if (_str == s) return true;
        if (_len != strlen(s)) return false;
        return strncmp(_str, s, _len) == 0;
    }

protected:
private:
    const char* _str;
    int _len;
};

} // namespace Util

#endif // CONSTSTRING_H
