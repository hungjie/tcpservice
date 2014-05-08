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

#include "websockethanlder.h"
#include <map>
#include <sstream>

#include "../util/util.h"

#pragma pack(1)
struct WebSocket_data_t{
    union{
        unsigned char c;
        struct {
            unsigned char op:4;
            unsigned char rsv: 3;
            unsigned char fin: 1;
        };
        
    };
    
    unsigned char len_0:7;
    unsigned char mask: 1;
    
    union{
        struct {
            unsigned char mask_dada_0 [4];
            char data_0[1];
        };
        struct {
            unsigned short int len_1;
            unsigned char mask_dada_1 [4];
            char data_1[1];
        };
        struct {
            long int len_2;
            unsigned char mask_dada_2 [4];
            char data_2[1];
        };
    };
};

struct WebSocket_data_nomask_t{
    union{
        unsigned char c;
        struct {
            unsigned char op:4;
            unsigned char rsv: 3;
            unsigned char fin: 1;
        };
        
    };
    
    unsigned char len_0:7;
    unsigned char mask: 1;
    
    union{

            
        char data_0[1];

        struct {
            unsigned short int len_1;
            char data_1[1];
        };
        struct {
            long int len_2;
            char data_2[1];
        };
    };
};
#pragma pack()


int WebSocketHanlder::do_handle_output(int sock, const char* buf, size_t len)
{
    WebSocket_data_nomask_t data;
    data.c = 0x81;
    data.mask = 0;
    size_t data_size = 2;
    if (len < 126) {
        data.len_0 = len; 
    } else if (len > 126 && len < 0xFFFF){
        data.len_0 = 126;
        data.len_1 = htons((short int)len);
        data_size = 4;
    } else {
        return -1; // TODO
        data.len_0 = 127;
        data.len_2 = len;
        data_size = 10;
    }
    write(sock, &data, data_size);
    write(sock, buf, len);
    return len;

}

int WebSocketHanlder::do_handle_input(int sock, char*& buf, size_t len)
{
    int r = read(sock, buf, len);
    
    buf[r] = 0;
        
    unsigned long data_len;
    unsigned char* mask;
    char* data_p;

    if (r > 0) {
        WebSocket_data_t *data = (WebSocket_data_t *) buf;
        data_len = data->len_0;
        mask = data->mask_dada_0;
        data_p =  data->data_0;        
        
        if (data->len_0 == 126) {
            data_len = ntohs(data->len_1);
            mask =data->mask_dada_1;
            data_p = data->data_1;
            
        } else if (data->len_0 == 127){
            return -1; // TODO
            data_len = data->len_2;
            mask =data->mask_dada_2;
            data_p = data->data_2;
        }
        
        if (data_len > len - (data_p - buf)) return -1;
        while (data_len + (data_p - buf) > r){
            r += read(sock, buf + r, data_len + (data_p - buf) - r);
        }
        
        for (int i = 0; i < data_len; ++i){
            data_p[i] ^= mask[i % 4];
        }
        buf = data_p;
        return data_len;
        
    }

    if (r == 0) return -1;

    if (errno == EAGAIN || errno == EWOULDBLOCK) {
        len = 0;
        return 0;
    }
    return -1;
}

int WebSocketHanlder::do_handle_handshake(int sock, char*& buf, size_t len)
{
    const char* const WEBSOCKET_GUID = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
    const char* const WEBSOCKET_VERSION = "13";
    int l = read(sock, buf, len);
    
    if (l <1) return -1;
    buf[l] = 0;

    char* str1 = 0;
    char* k,*v;

    map<string, const char*> header;

    //string s;
    k = strtok_r(buf, "\r\n", &str1);

    while(k = strtok_r(0, "\r\n", &str1)) {
        v = strstr(k, ": ");
        if (!v) continue;
        *v = 0;
        v+=2;
        header[k] = v;
    }

    if (header.find("Connection") != header.end())
    {
        const char* s = header["Connection"];
        if (strstr(s, "Upgrade") == 0) return -1;
    }

    if (header.find("Upgrade") != header.end()) {
        const char* s = header["Upgrade"];
        if (strcmp(s, "websocket") != 0) return -1;
    }
    
    if (header.find("Sec-WebSocket-Version") != header.end()) {
        const char* s = header["Sec-WebSocket-Version"];
        if (strcmp(s, WEBSOCKET_VERSION) != 0) return -1;
    }

    string key = string(header["Sec-WebSocket-Key"]) + WEBSOCKET_GUID;

    vector<unsigned int> vec;
    sha1_encode(key.c_str(), key.length(), vec);
    
    vector<char> vv;
    for(vector<unsigned int>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        
        vv.push_back((char)((*it) >> 24));
        vv.push_back((char)((*it) >> 16));
        vv.push_back((char)((*it) >> 8));
        vv.push_back((char)((*it) >> 0));
    }
    
     
    key = base64_encode(&vv[0], vv.size());

    snprintf(buf, len, "HTTP/1.1 101 Switching Protocols\r\n"
             "Upgrade: websocket\r\n"
             "Connection: Upgrade\r\n"
             "Sec-WebSocket-Accept: %s\r\n"
             "\r\n", key.c_str());


    write(sock, buf, strlen(buf));

    return len;
}
