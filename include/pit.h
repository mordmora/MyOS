#ifndef KPIT_H
#define KPIT_H
#include "idt.h"
#include "types.h"

void timer_callback(reg_frame_t* regs);

void init_pit(uint32_t freq);

#endif