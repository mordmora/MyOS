#include "serial.h"
#include "io.h"

void serial_configure_baud_rate(unsigned short com, unsigned short div){
    outb(SERIAL_LINE_CMD_PORT(com), SERIAL_LINE_ENABLE_DBLAB);
    outb(SERIAL_DATA_PORT(com), ((div >> 8) & 0x00FF));
    outb(SERIAL_DATA_PORT(com), (div & 0x00FF));
}

void serial_configure_line(unsigned short com){
    /*
        d |  b |   prty   |  s |  dl  |
        0    0   0   0   0   0   1   1
    */
    outb(SERIAL_LINE_CMD_PORT(com), 0x03);
}

void serial_configure_fifo(unsigned short com){
    outb(SERIAL_FIFO_CMD_PORT(com), 0xC7);
}

void serial_configure_modem(unsigned short com){
    outb(SERIAL_MODEM_CMD_PORT(com), 0x03);
}

int serial_transmit_fifo_empty(unsigned int com){
    return inb(SERIAL_LINE_STATUS_CMD_PORT(com)) & 0x20;
}

int serial_write(const char* buff, unsigned int len, unsigned int com){

    for(unsigned int i = 0; i < len; ++i){

        while(!serial_transmit_fifo_empty(com)){}
    
        outb(SERIAL_DATA_PORT(com), buff[i]);

    }
    return 0;

}