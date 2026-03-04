#include "idt.h"
#include "debug.h"
#include "printf.h"
__attribute__((aligned(0x10))) static idt_entry_t idt[256];

static idtr_t idtr;

__attribute__((noreturn))
void isr_exception_handler(reg_frame_t*);
void isr_exception_handler(reg_frame_t* regs){

    DEBUG_FB("Interrupcion encontrada");
    kprintf_fb("INT: %d  Error: %d\n", regs->int_no, regs->err_code);
    kprintf_fb("EIP: 0x%x  CS: 0x%x  EFLAGS: 0x%x\n", regs->eip, regs->cs, regs->eflags);
    kprintf_fb("EAX: 0x%x  EBX: 0x%x\n", regs->eax, regs->ebx);

    if(regs->int_no == 0){
        ERROR_ALL("Por que divides entre 0?");
    }else if(regs->int_no == 3){
        DEBUG_FB("BREAKPOINT");
    }

    for(;;)
        __asm__ volatile ("cli; hlt");
}

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags){
    idt_entry_t* desc = &idt[vector];

    desc->isr_low = (uint32_t)isr & 0xFFFF;
    desc->kernel_cs = 0x08;
    desc->zero = 0;
    desc->attributes = flags;
    desc->isr_high = (uint32_t)isr >> 16;
}

static uint8_t vectors[IDT_MAX_DESCRIPTORS];

extern void* isr_stub_table[];

void init_idt(){
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)(sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1);

    for(uint8_t v = 0; v < 32; v++){
        idt_set_descriptor(v, isr_stub_table[v], 0x8E);
        vectors[v] = 1;
    }

    __asm__ volatile("lidt %0" :: "m"(idtr));

   // for(;;);
    //__asm__ volatile("sti");
    //__asm__ volatile("int $3");
}