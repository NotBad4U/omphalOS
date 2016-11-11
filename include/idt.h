#ifndef IDT_H
#define IDT_H

#include "types.h"

#define IDTSIZE	0xFF /* max number of idt descriptor */
#define IDTBASE	0x00000000	/*base address of idtr */
#define KERNEL_CS 0x08

typedef struct {
    uint16 lowOffset;
    uint16 select;
    uint8 always0;
    uint8 flags;
    uint16 highOffset;
} __attribute__((packed)) idtDesc_t ;

typedef struct {
    uint16 limit;
    uint32 base;
} __attribute__((packed)) idtr_t;


/* Functions implemented in idt.c */
void setIdtDesc(int n, uint32 handler);
void initIdtr();
void initPic();

#endif
