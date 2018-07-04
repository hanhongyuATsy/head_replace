
#ifndef _LOG_DEF_H
#define _LOG_DEF_H


#include <stdlib.h>  
#include <stdio.h>  
  
//#define _DEBUG

//替换函数名  
#ifndef _DEBUG  
#define LOGFUNC(...) do{}while(0)  
#else  
#define LOGFUNC(format, ...) do {\
    printf("%s, (%d), <%s>" format,\
            __FILE__, __LINE__ , __func__, ##__VA_ARGS__);\
}while(0)
#endif  
  






#endif
