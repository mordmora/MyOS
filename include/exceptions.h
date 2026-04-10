#ifndef KEXCEPTIONS_H
#define KEXCEPTIONS_H
#include "idt.h"

void zero_div(reg_frame_t* regs);


void init_exceptions();


#endif