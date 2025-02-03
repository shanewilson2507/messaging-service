#ifndef MESSAGING_SERVICE_COMMON_HPP
#define MESSAGING_SERVICE_COMMON_HPP

#include <stdarg.h>
#include <stdint.h>
#include <iostream>
#include <string.h>
#include <arpa/inet.h>


#ifdef MESSAGING_SERVICE_DEBUG
    #define debug_print(string) do {std::cout<<string<<std::endl;} while (0)
#else
    #define debug_print(string) 
#endif //#ifdef MESSAGING_SERVICE_DEBUG



#endif // #ifndef MESSAGING_SERVICE_COMMON_H