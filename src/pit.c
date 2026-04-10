#include "pit.h"
#include "idt.h"
#include "io.h"
#include "types.h"
#include "debug.h"

static int tick_count = 0;

void init_pit(uint32_t freq){

    register_interrupt_handler(32, timer_callback);

    uint32_t div = 1193188 / freq;

    outb(0x43, 0x36);

    outb(0x40, (uint8_t)(div & 0xFF));
    outb(0x40, (uint8_t)(div >> 8) & 0xFF);

    DEBUG_ALL("pit initialized");

}

void timer_callback(reg_frame_t* regs){
    (void)regs->cs;
    kprintf("[TIMER] Tick %d\n", tick_count);
    tick_count++;
}