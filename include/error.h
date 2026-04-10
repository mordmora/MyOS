#ifndef KERROR_H
#define KERROR_H

#include "printf.h"

#define panic(fmt) do {\
        kprintf("kernel say: PANIC!!!!! [file: " __FILE__ ", line: %d]\n", __LINE__);\
        print_cow(fmt);                                                               \
        for(;;){ __asm__ volatile("cli; hlt");  }                                      \
    } while(0)



void print_cow(const char *error_msg);


#endif