bits    32

global start
extern kmain


%define MULTIBOOT_HEADER_MAGIC  0x1BADB002
%define MULTIBOOT_HEADER_FLAGS	0x00000003
%define CHECKSUM -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)


section .text
    align   4
    dd MULTIBOOT_HEADER_MAGIC
    dd MULTIBOOT_HEADER_FLAGS
    dd CHECKSUM


start:
    cli             ;clear the interrupts
    call kmain
    cli             ; stop interrupts
    hlt             ; halt the cpu
