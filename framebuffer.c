#include "framebuffer.h"
#include "io.h"
char* fb = (char*) 0x000B8000;
unsigned short cursor_pos = 0;

void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg){
    fb[i] = c;
    fb[i+1] = ((bg & 0x0F) << 4 | (fg & 0x0F));
}

void fb_move_cursor(unsigned short pos){
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_CMD);
    outb(FB_DATA_PORT, ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_CMD);
    outb(FB_DATA_PORT, (pos & 0x00FF));
}

void fb_scroll(){
    for(unsigned int i = 0; i < (FB_ROWS - 1) * FB_COLUMNS; i++){
        fb[i * 2] = fb[(i + FB_COLUMNS) * 2];         
        fb[i * 2 + 1] = fb[(i + FB_COLUMNS) * 2 + 1];
    }

    unsigned int last_line_start = (FB_ROWS - 1) * FB_COLUMNS;
    for(unsigned int i = 0; i < FB_COLUMNS; i++){
        fb_write_cell((last_line_start + i) * 2, ' ', FB_COLOR_LIGHT_GRAY, FB_COLOR_BLACK);
    }
    
    cursor_pos = last_line_start;
}

int fb_write(const char* buff, unsigned int len){
        
    for(unsigned int i = 0; i < len; i++){
        if(cursor_pos >= FB_SIZE){
            fb_scroll();
        }
        
        if(buff[i] == '\n'){
            unsigned char current_row = cursor_pos / FB_COLUMNS;
            cursor_pos = (current_row + 1) * FB_COLUMNS;
        }else if (buff[i] == '\t'){
            cursor_pos += 4;
        }else{
            fb_write_cell(cursor_pos * 2, buff[i], FB_COLOR_LIGHT_GRAY, FB_COLOR_BLACK);
            cursor_pos++;
        }
        
        fb_move_cursor(cursor_pos);
    }

    return len;
}

void fb_clear(){
    for(unsigned int i = 0; i < FB_SIZE; i++){
        fb_write_cell(i * 2, ' ', FB_COLOR_BLACK, FB_COLOR_BLACK);
    }
    cursor_pos = 0;
    fb_move_cursor(0);
}