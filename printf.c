#include "printf.h"
#include "serial.h"
#include "framebuffer.h"
#include "strings.h" 

static void itoa(int value, char* buffer, int base) {
    char* ptr = buffer;
    char* ptr1 = buffer;
    char tmp_char;
    int tmp_value;

    if (base < 2 || base > 36) { *buffer = '\0'; return; }
    if (value < 0 && base == 10) {
        *ptr++ = '-';
        ptr1++; 
        value = -value; 
    }

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "0123456789abcdef"[tmp_value - value * base];
    } while (value);

    *ptr-- = '\0';

    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }
}

static void uitoa(unsigned int value, char* buffer, int base) {
    char* ptr = buffer;
    char* ptr1 = buffer;
    char tmp_char;
    unsigned int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "0123456789abcdef"[tmp_value - value * base];
    } while (value);

    *ptr-- = '\0';

    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr-- = *ptr1;
        *ptr1++ = tmp_char;
    }
}

// Envía un carácter
static void kputc(char c, unsigned char device) {
    if (device == KPRINTF_SERIAL || device == KPRINTF_ALL) {
        serial_write(&c, 1, SERIAL_COM_BASE); 
    } 
    if (device == KPRINTF_FRAMEBUFFER || device == KPRINTF_ALL) {
        fb_write(&c, 1);
    }
}

static void kputs(const char* str, unsigned char device) {
    while (*str) {
        kputc(*str++, device);
    }
}


static int kvprintf(unsigned char device, const char* format, va_list args) {
    int chars_written = 0;
    const char* ptr = format;
    char numBuffer[32]; 

    while (*ptr) {
        if (*ptr == '%') {
            ptr++;
            switch (*ptr) {
                case 's': {
                    const char* str = va_arg(args, const char*);
                    if (!str) str = "(null)";
                    kputs(str, device);
                    chars_written += strlen(str);
                    break;
                }
                case 'd':
                case 'i': {
                    int value = va_arg(args, int);
                    itoa(value, numBuffer, 10);
                    kputs(numBuffer, device);
                    chars_written += strlen(numBuffer);
                    break;
                }
                case 'u': {
                    unsigned int value = va_arg(args, unsigned int);
                    uitoa(value, numBuffer, 10);
                    kputs(numBuffer, device);
                    chars_written += strlen(numBuffer);
                    break;
                }
                case 'x': {
                    unsigned int value = va_arg(args, unsigned int);
                    uitoa(value, numBuffer, 16);
                    kputs(numBuffer, device);
                    chars_written += strlen(numBuffer);
                    break;
                }
                case 'p': {
                    void* ptr_value = va_arg(args, void*);
                    kputs("0x", device);
                    uitoa((unsigned long)ptr_value, numBuffer, 16);
                    kputs(numBuffer, device);
                    chars_written += strlen(numBuffer) + 2;
                    break;
                }
                case 'c': {
                    char c = (char)va_arg(args, int);
                    kputc(c, device);
                    chars_written++;
                    break;
                }
                case '%': {
                    kputc('%', device);
                    chars_written++;
                    break;
                }
                default: 
                    kputc('%', device);
                    kputc(*ptr, device);
                    chars_written += 2;
                    break;
            }
        } else {
            kputc(*ptr, device);
            chars_written++;
        }
        ptr++;
    }
    return chars_written;
}

int kprintf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    int ret = kvprintf(KPRINTF_FRAMEBUFFER, format, args);
    va_end(args);
    return ret;
}

int kprintf_device(unsigned char device, const char* format, ...) {
    va_list args;
    va_start(args, format);
    int ret = kvprintf(device, format, args);
    va_end(args);
    return ret;
}

int kprintf_serial(const char* format, ...) {
    va_list args;
    va_start(args, format);
    int ret = kvprintf(KPRINTF_SERIAL, format, args);
    va_end(args);
    return ret;
}

int kprintf_fb(const char* format, ...) {
    va_list args;
    va_start(args, format);
    int ret = kvprintf(KPRINTF_FRAMEBUFFER, format, args);
    va_end(args);
    return ret;
}