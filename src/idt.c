#include "idt.h"
#include "debug.h"
#include "printf.h"
#include "error.h"
#include "pic.h"
__attribute__((aligned(0x10))) static idt_entry_t idt[256];

static idtr_t idtr;

static isr_t interrup_handlers[256] = {0};

void register_interrupt_handler(uint8_t n, isr_t handler){
  interrup_handlers[n] = handler;
}

void isr_exception_handler(reg_frame_t *regs) {

  if(interrup_handlers[regs->int_no] != 0){

    interrup_handlers[regs->int_no](regs);

  }else{
    kprintf("Interrupción %d no registrada\n", regs->int_no);
    if(regs->int_no < 32){
      
      panic("this shit is coocked.");

    }
  }

  if(regs->int_no >= 32 && regs->int_no <= 47){
    send_eoi(regs->int_no - 32);
  }

}

void idt_set_descriptor(uint8_t vector, void *isr, uint8_t flags) {
  idt_entry_t *desc = &idt[vector];

  desc->isr_low = (uint32_t)isr & 0xFFFF;
  desc->kernel_cs = 0x08;
  desc->zero = 0;
  desc->attributes = flags;
  desc->isr_high = (uint32_t)isr >> 16;
}

static uint8_t vectors[IDT_MAX_DESCRIPTORS];

extern void *isr_stub_table[];

void init_idt() {
 // DEBUG_SERIAL("initializing idt");
  idtr.base = (uintptr_t)&idt[0];
  idtr.limit = (uint16_t)(sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1);

  for (uint8_t v = 0; v < 48; v++) {
    idt_set_descriptor(v, isr_stub_table[v], 0x8E);
    vectors[v] = 1;
  }

  __asm__ volatile("lidt %0" ::"m"(idtr));

  // for(;;);
  //__asm__ volatile("sti");
  //__asm__ volatile("int $3");
}