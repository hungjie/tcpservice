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

#include "../pch.h"
// #include <openssl/sha.h>
// #include <openssl/evp.h>

#include <boost/uuid/sha1.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/transform_width.hpp>

#include <vector>
#include <sstream>

#include "util.h"

void sha1_encode(const char* buf, size_t len, vector<unsigned int> &out){
    boost::uuids::detail::sha1 sha;
    sha.process_bytes(buf, len);
    
    out.resize(5);
    unsigned int (*p)[5] = (unsigned int(*)[5]) (&out[0]);
    sha.get_digest(*p);

}

string base64_encode(const char* in, size_t len){ 
  typedef boost::archive::iterators::base64_from_binary<boost::archive::iterators::transform_width<string::const_iterator, 6, 8> > Base64EncodeIterator;  
  stringstream result;  
  copy(Base64EncodeIterator(in) , Base64EncodeIterator(in + len), ostream_iterator<char>(result));  
  size_t equal_count = (3 - len % 3) % 3;  
  for (size_t i = 0; i < equal_count; i++) {  
    result.put('=');  
  }  
   
  return result.str();   
}

// void sha1_encode(unsigned char* buf, const char* s, size_t len){
//     SHA_CTX ctx;
//     SHA1_Init(&ctx);
//     
//     SHA1_Update(&ctx, s, len);
//     SHA1_Final(buf, &ctx);
//     OPENSSL_cleanse(&ctx, sizeof(ctx));
// }

