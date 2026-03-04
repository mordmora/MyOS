extern kernel_main

global loader

    MAGIC_NUM equ 0x1BADB002
    FLAGS equ 0x0
    CHECKSUM equ -MAGIC_NUM

    KERNEL_STACK_SIZE equ 4096

    section .bss
    align 4
    kernel_stack:
        resb KERNEL_STACK_SIZE

    section .text
    align 4
        dd MAGIC_NUM
        dd FLAGS
        dd CHECKSUM    

    loader:
        mov eax, 0xCAFEBABE
        mov esp, kernel_stack + KERNEL_STACK_SIZE

        call kernel_main
    
   .loop:
       jmp .loop