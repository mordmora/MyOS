
#include "debug.h"
#include "gdt.h"
#include "idt.h"
#include "io.h"
#include "printf.h"
#include "strings.h"
#include "types.h"
#include "exceptions.h"
#include "pic.h"
#include "pit.h"

void init_routine() {
  fb_clear();
  DEBUG_ALL("Framebuffer cleaned\n");
  init_gdt();
  DEBUG_ALL("global descriptor table initalized\n");
  init_idt();
  DEBUG_ALL("interrupt descriptor table initialized\n");

  __asm__ volatile("cli");

  init_exceptions();
  init_pic();
  init_pit(100);
  __asm__ volatile("sti");


}

__attribute__((noreturn)) void kernel_main(void) {
  init_routine();
  kprintf("[STARTED] kernel v1.1\n");

  //volatile int a = 10;
  //volatile int b = 0;
  //int c = a / b;
  //(void)c;
  //__asm__ volatile("int $3");
  //
  for (;;)
    __asm__ volatile("hlt");
}
