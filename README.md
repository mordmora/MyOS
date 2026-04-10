# MyOS

Kernel educativo en C y ensamblador x86 de 32 bits, booteable con GRUB y ejecutable en QEMU.

## Estado actual

- Arranque de kernel ELF (`kernel.elf`) con imagen ISO (`os.iso`).
- Inicializacion de GDT e IDT.
- Manejo basico de excepciones (ejemplo: division por cero).
- Remapeo y manejo de PIC (EOI para IRQs).
- Inicializacion de PIT a frecuencia configurable (actualmente 100 Hz).
- Salida por framebuffer, serial y `kprintf` para debug.

## Requisitos

Necesitas herramientas de compilacion para 32 bits y utilidades de emulacion:

- `gcc` (con soporte `-m32`)
- `ld` (binutils)
- `nasm`
- `genisoimage`
- `qemu-system-i386`
- `make`

En Debian/Ubuntu, normalmente:

```bash
sudo apt update
sudo apt install build-essential gcc-multilib binutils nasm genisoimage qemu-system-x86
```

## Compilar y ejecutar

Desde la raiz del proyecto:

```bash
make
```

Genera:

- `kernel.elf`
- objetos en `build/`

Para crear la ISO:

```bash
make os.iso
```

Para ejecutar en QEMU:

```bash
make run
```

Para limpiar artefactos:

```bash
make clean
```

## Estructura del proyecto

```text
include/   Headers del kernel
src/       Codigo fuente C/ASM
iso/       Arbol de arranque para GRUB
build/     Objetos intermedios (.o)
link.ld    Script de enlace
Makefile   Build principal
```

## Flujo de inicializacion

En `kernel_main` se ejecuta el siguiente orden general:

1. Limpieza de framebuffer.
2. Inicializacion de GDT.
3. Inicializacion de IDT.
4. `cli` para configurar interrupciones de forma segura.
5. Registro de excepciones, inicializacion de PIC y PIT.
6. `sti` para habilitar interrupciones.
7. Loop infinito con `hlt`.

## Notas de debug

- El timer imprime ticks con `kprintf` desde la IRQ0.
- Hay macros de debug/error para framebuffer y serial.
- Puedes probar una excepcion habilitando el bloque comentado en `kernel_main`.
