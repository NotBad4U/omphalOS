#ifndef GDT_H
#define GDT_H

#define GDTSIZE		0xFF	    /* nb max of descriptors in a table */
#define GDTBASE		0x00000800	/* physical address of the gdt */

#define SEGMENT_CODE_USER   0x30000     /* Segment for code user (arbitrary value)*/
#define SEGMENT_STACK_USER  0x20000     /* Segment for stack user (arbitrary value)*/

#include "types.h"
#include "util.h"

/* Reference the system where the gdt is initialized */
typedef struct {
    uint16 limite;
    uint32 base;
} __attribute__ ((packed)) gdtr_t;

/* Global descriptor table
Describe segment */
typedef struct {
    uint16 lim0_15;
    uint16 base0_15;
    uint8 base16_23;
    uint8 acces;
    uint8 lim16_19 : 4;
    uint8 other : 4;
    uint8 base24_31;
} __attribute__ ((packed)) gdtdesc_t;

typedef struct {
    uint16 previousTask, previousTaskReserved;
    uint32 esp0; // ESP0 gets the value the stack-pointer shall get at a system call
    uint16 ss0, ss0Reserved; // SS0 gets the kernel datasegment descriptor
    uint32 esp1;
    uint16 ss1, ss1Reserved;
    uint32 esp2;
    uint16 ss2, ss2Reserved;
    uint32 cr3;
    uint32 eip;
    uint32 eflags;
    uint32 eax, ecx, edx, ebx;
    uint32 esp;
    uint32 ebp;
    uint32 esi;
    uint32 edi;
    uint16 es, esReserved;
    uint16 cs, csReserved;
    uint16 ss, ssReserved;
    uint16 ds, dsReserved;
    uint16 fs, fsReserved;
    uint16 gs, gsReserved;
    uint16 ldtSegmentSelector, ldtSegmentSelectorReserved;
    uint16 debugFlag, ioMapBaseAddres;

} __attribute__((packed)) tss_t ;


void initGdt(void);

void init_gdt_desc(uint32 base, uint32 limite, uint8 acces, uint8 other, gdtdesc_t *desc);

#endif /* IDT_H */
