#ifndef __LOG__
#define __LOG__

#include "pch.h"

class Log{
public:
  void output(const char* s){
    
  }
  
  Log(const char* filename){
    _f = fopen(filename, "a");
  }
  ~Log(){
    fclose(_f);
  }
private:
  FILE* _f;  
  char _buffer[2048];
  
};

#endif // __LOG__