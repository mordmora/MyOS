#ifndef PRINTF_H
#define PRINTF_H

#define KPRINTF_SERIAL 0
#define KPRINTF_FRAMEBUFFER 1
#define KPRINTF_ALL 2
typedef __builtin_va_list va_list;
#define va_start(ap, last) __builtin_va_start(ap, last)
#define va_arg(ap, type) __builtin_va_arg(ap, type)
#define va_end(ap) __builtin_va_end(ap)

int kprintf(const char* format, ...);
int kprintf_serial(const char* format, ...);
int kprintf_fb(const char* format, ...);

#endif