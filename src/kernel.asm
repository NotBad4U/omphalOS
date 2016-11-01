bits    32


%define MULTIBOOT_HEADER_MAGIC  0x1BADB002                           ; Indicate the address header for the bootloader
%define MULTIBOOT_HEADER_FLAGS	0x00000003                           ; Set the multiboot flag
%define CHECKSUM -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)  ; To prove we are multiboot

; Define the multiboot header that marks the program as a kernel
section .multiboot
    align   4
    dd MULTIBOOT_HEADER_MAGIC
    dd MULTIBOOT_HEADER_FLAGS
    dd CHECKSUM

; The multiboot standard does not define the value of the stack pointer register
; (esp) and it is up to the kernel to provide a stack.
section .bss
    align 4
stack_bottom:
    resb 16384 ; 16 KiB
stack_top:



section .text
global start
extern kmain

start:
    mov esp, stack_top  ; Set up the stack pointer
    call kmain
    cli                 ; Stop interrupts
.hang:                  ; If the system has nothing more to do we put the computer into an infinite loop.
    hlt                 ; Halt instruction
    jmp .hang
.end:
