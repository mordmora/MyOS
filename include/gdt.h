#ifndef GDT_H
#define GDT_H

struct gdt {
  unsigned short size;
  unsigned int addresses;
} __attribute__((packed));

struct gdt_descriptor {
  unsigned short limit;
  unsigned short base_l;
  unsigned char base_mid;
  unsigned char access;
  unsigned char flimits; // flags and limits 0 - 3 -> limit | 4 - 7 -> flags
  unsigned char base_high;
} __attribute__((packed));

typedef struct gdt gdt_t;
typedef struct gdt_descriptor gdt_descriptor_t;

extern void gdt_flush(unsigned int);

void init_gdt();

#endif