
#include "types.h"
#include "io.h"
#include "strings.h"
#include "gdt.h"
#include "printf.h"
#include "debug.h"
#include "idt.h"

void init_routine(){
    fb_clear();
    init_gdt();
    init_idt();

}

__attribute__((noreturn))
void kernel_main(void){
    init_routine();
    kprintf("[STARTED] kernel v1.1\n");

    //volatile int a = 10;
    //volatile int b = 0;
    //int c = a / b;
    //(void)c;
    //__asm__ volatile("int $3");
}