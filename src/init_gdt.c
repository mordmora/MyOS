#include "debug.h"
#include "gdt.h"
#include "printf.h"
#include "types.h"
volatile gdt_t gdt;
volatile gdt_descriptor_t entries[3];

void init_table_segment(unsigned int i, unsigned int base, unsigned int limit,
                        unsigned char access, unsigned char gran) {

  entries[i].base_l = (base & 0xFFFF);
  entries[i].base_mid = (base >> 16) & 0xFF;
  entries[i].base_high = (base >> 24) & 0xFF;

  entries[i].limit = limit & 0xFFFF;
  entries[i].flimits = (limit >> 16) & 0x0F;
  entries[i].flimits |= gran & 0xF0;

  entries[i].access = access;
}

void print_gdt_layout(uint32_t i) {
  kprintf("gdt_ptr:\n\tbase_low: %p\n\tbase_mid: %p\n\tbase_high: %p\n\tlimit: "
          "%p\n\tflimits: %p\n\taccess: %p\n",
          entries[i].base_l, entries[i].base_mid, entries[i].base_high,
          entries[i].limit, entries[i].flimits, entries[i].access);
}

void init_gdt() {
  // DEBUG_ALL("Sizeof GDT: %d\n", sizeof(gdt_t));
  // DEBUG_ALL("Sizeof Entry: %d\n", sizeof(gdt_descriptor_t));
  gdt.addresses = (uint32_t)&entries;
  // DEBUG_ALL("gdt initialized in %p", (void *)gdt.addresses);
  gdt.size = (sizeof(gdt_descriptor_t) * 3 - 1);

  init_table_segment(0, 0, 0, 0, 0); // NULL

  init_table_segment(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // kmode code segment

  init_table_segment(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // kmode data segment

  DEBUG_FB("NULL segment");
  print_gdt_layout(0);
  DEBUG_FB("Code segment");
  print_gdt_layout(1);
  DEBUG_FB("Data segment");
  print_gdt_layout(2);
  gdt_flush((uint32_t)&gdt);
}