#ifndef DEBUG_H
#define DEBUG_H

#include "io.h"
#include "printf.h"

#define DEBUG_FB(fmt, ...) kprintf("[DEBUG] " fmt "\n", ##__VA_ARGS__)
#define INFO_FB(fmt, ...) kprintf("[INFO] " fmt "\n", ##__VA_ARGS__)
#define WARN_FB(fmt, ...) kprintf("[WARN] " fmt "\n", ##__VA_ARGS__)
#define ERROR_FB(fmt, ...) kprintf("[ERROR] " fmt "\n", KPRINTF_FRAMEBUFFER, ##__VA_ARGS__)

#define DEBUG_SERIAL(fmt, ...) kprintf("[DEBUG] " fmt "\n", ##__VA_ARGS__)
#define INFO_SERIAL(fmt, ...) kprintf("[INFO] " fmt "\n", ##__VA_ARGS__)
#define WARN_SERIAL(fmt, ...) kprintf("[WARN] " fmt "\n", ##__VA_ARGS__)
#define ERROR_SERIAL(fmt, ...) kprintf("[ERROR] " fmt "\n", ##__VA_ARGS__)

#define DEBUG_ALL(fmt, ...) do { \
    kprintf_fb("[DEBUG] " fmt "\n", ##__VA_ARGS__); \
    kprintf_serial("[DEBUG] " fmt "\n", ##__VA_ARGS__); \
} while(0)

#define INFO_ALL(fmt, ...) do { \
    kprintf_fb("[INFO] " fmt "\n", ##__VA_ARGS__); \
    kprintf_serial("[INFO] " fmt "\n", ##__VA_ARGS__); \
} while(0)

#define WARN_ALL(fmt, ...) do { \
    kprintf_fb("[WARN] " fmt "\n", ##__VA_ARGS__); \
    kprintf_serial("[WARN] " fmt "\n", ##__VA_ARGS__); \
} while(0)

#define ERROR_ALL(fmt, ...) do { \
    kprintf_fb("[ERROR] " fmt "\n", ##__VA_ARGS__); \
    kprintf_serial("[ERROR] " fmt "\n", ##__VA_ARGS__); \
} while(0)

#define KASSERT(condition, msg) do { \
    if (!(condition)) { \
        kprintf("[ASSERT FAILED] %s:%d - %s\n", __FILE__, __LINE__, msg); \
        kprintf("[ASSERT FAILED] %s:%d - %s\n", __FILE__, __LINE__, msg); \
        while(1); \
    } \
} while(0)

#endif 