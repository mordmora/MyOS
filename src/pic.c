#include "types.h"
#include "pic.h"
#include "io.h"

void pic_ack(uint8_t _irq){
    if(_irq >= 8) outb(PIC_SLAVE_CMD, PIC_EOI_CMD);
    outb(PIC_MASTER_CMD, PIC_EOI_CMD);
}

void init_pic(){

    outb(PIC_MASTER_CMD, 0x11);
    io_wait();
    outb(PIC_SLAVE_CMD, 0x11);
    io_wait();
    outb(PIC_MASTER_DATA, 0x20);
    io_wait();
    outb(PIC_SLAVE_DATA, 0x28);
    io_wait();
    outb(PIC_MASTER_DATA, 0x4);
    io_wait();
    outb(PIC_SLAVE_DATA, 0x2);
    io_wait();
    outb(PIC_MASTER_DATA, 0x1);
    io_wait();
    outb(PIC_SLAVE_DATA, 0x1);
    io_wait();

    outb(PIC_MASTER_DATA, 0);
    io_wait();
    outb(PIC_SLAVE_DATA, 0);
}

void pic_disable(){
    outb(PIC_MASTER_DATA, 0xff);
    outb(PIC_SLAVE_DATA, 0xff);
}

void send_eoi(uint8_t irq){
    pic_ack(irq);
}