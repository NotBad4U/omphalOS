#ifndef IDT_H
#define IDT_H

#define GDTSIZE		0xFF	    /* nb max of descriptors in a table */
#define GDTBASE		0x00000800	/* physical address of the gdt */


#include "types.h"
#include "util.h"

/* Reference the system where the gdt is initialized */
struct gdtr {
    uint16 limite;
    uint32 base;
} __attribute__ ((packed));

/* Global descriptor table
Describe segment */
struct gdtdesc {
    uint16 lim0_15;
    uint16 base0_15;
    uint8 base16_23;
    uint8 acces;
    uint8 lim16_19 : 4;
    uint8 other : 4;
    uint8 base24_31;
} __attribute__ ((packed));


void init_gdt_desc(uint32 base, uint32 limite, uint8 acces, uint8 other, struct gdtdesc *desc);

void init_gdt();

#endif /* IDT_H */
