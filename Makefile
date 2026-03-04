OBJECTS = loader.o kmain.o io.o strings.o serial.o framebuffer.o gdt.o init_gdt.o printf.o idt.o isr.o
CC = gcc
CFLAGS = -m32 -nostdlib -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c

LDFLAGS = -T link.ld -melf_i386
AS = nasm 
ASFLAGS = -f elf

all: kernel.elf

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

%.o: %.c 
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean: 
	rm -rf *.o kernel.elf os.iso 