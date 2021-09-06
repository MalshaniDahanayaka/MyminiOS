
global loader


KERNEL_STACK_SIZE equ 4096


MODULEALIGN equ 1 << 0

MEMINFO equ 1 << 1

FLAGS equ MODULEALIGN | MEMINFO

MAGIC_NUMBER equ 0x1BADB002

CHECKSUM equ - (MAGIC_NUMBER + FLAGS)

extern KERNEL_PHYSICAL_START

extern KERNEL_PHYSICAL_END

section .bss

align 4

KERNEL_STACK:
    
    resb KERNEL_STACK_SIZE


section .text

align 4
   
    dd MAGIC_NUMBER
    
    dd FLAGS

    dd CHECKSUM

loader:
    
    mov esp, KERNEL_STACK + KERNEL_STACK_SIZE

    extern kmain

    push $KERNEL_PHYSICAL_END

    push $KERNEL_PHYSICAL_START

    call kmain
    .loop:

      jmp .loop
