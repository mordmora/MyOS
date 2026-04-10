#ifndef KIO_H
#define KIO_H

#include "serial.h"
#include "framebuffer.h"

extern void outb(unsigned short port, unsigned short data);

extern int inb(unsigned short port);

extern int io_wait();

#endif