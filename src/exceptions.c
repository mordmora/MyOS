#include "exceptions.h"

#include "idt.h"
#include "error.h"
#include "debug.h"


void zero_div(reg_frame_t* regs){
    ERROR_ALL("zero div in ebx: %d", regs->ebx);
    panic("Why are you dividing by zero? dumb");
}

void init_exceptions(){
    register_interrupt_handler(0, zero_div);
}