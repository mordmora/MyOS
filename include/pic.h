#ifndef __PIC_H
#define __PIC_H

//#include "io.h"
#include "types.h"

#define PIC_MASTER_CMD 0x20
#define PIC_MASTER_DATA 0x21
#define PIC_SLAVE_CMD 0xA0
#define PIC_SLAVE_DATA 0xA1
#define PIC_EOI_CMD 0x20

void pic_ack(uint8_t _irq);

void send_eoi(uint8_t irq);

void pic_disable();

void init_pic();

void irq_mask();


#endif