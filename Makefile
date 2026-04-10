SRCDIR = src
INCDIR = include
BUILDDIR = build

OBJECTS = $(BUILDDIR)/loader.o \
          $(BUILDDIR)/kmain.o \
          $(BUILDDIR)/io.o \
          $(BUILDDIR)/strings.o \
          $(BUILDDIR)/serial.o \
          $(BUILDDIR)/framebuffer.o \
          $(BUILDDIR)/gdt.o \
          $(BUILDDIR)/init_gdt.o \
          $(BUILDDIR)/printf.o \
          $(BUILDDIR)/idt.o \
          $(BUILDDIR)/isr.o \
          $(BUILDDIR)/exceptions.o \
          $(BUILDDIR)/error.o \
          $(BUILDDIR)/pic.o \
          $(BUILDDIR)/pit.o

CC = gcc
CFLAGS = -m32 -nostdlib -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -I$(INCDIR) -c

LDFLAGS = -T link.ld -melf_i386
AS = nasm 
ASFLAGS = -f elf

all: $(BUILDDIR) kernel.elf

$(BUILDDIR):
	mkdir -p $(BUILDDIR)

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

os.iso: kernel.elf 
	cp kernel.elf iso/boot/kernel.elf
	genisoimage -R                          \
            -b boot/grub/stage2_eltorito    \
            -no-emul-boot                   \
            -boot-load-size 4               \
            -A os                           \
            -input-charset utf8             \
            -quiet                          \
            -boot-info-table                \
            -o os.iso                       \
            iso

run: os.iso
	qemu-system-i386 -cdrom os.iso -m 256 -boot d -serial stdio

$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) $< -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.s | $(BUILDDIR)
	$(AS) $(ASFLAGS) $< -o $@

clean: 
	rm -rf $(BUILDDIR) kernel.elf os.iso 