#include "gdt.h"
#include "screen.h"

static void initDefaultTss();

gdtdesc_t kgdt[GDTSIZE];	/* GDT with GDTSIZE segment */
gdtr_t kgdtr;              /* GDTR */
tss_t defaultTss;


void init_gdt_desc(uint32 base, uint32 limite, uint8 acces, uint8 other, gdtdesc_t *desc)
{
        desc->lim0_15 = (limite & 0xffff);
        desc->base0_15 = (base & 0xffff);
        desc->base16_23 = (base & 0xff0000) >> 16;
        desc->acces = acces;
        desc->lim16_19 = (limite & 0xf0000) >> 16;
        desc->other = (other & 0xf);
        desc->base24_31 = (base & 0xff000000) >> 24;
        return;
}


void initGdt(void)
{
    initDefaultTss();
    
    init_gdt_desc(0x0, 0x0, 0x0, 0x0, &kgdt[0]);
    init_gdt_desc(0x0, 0xFFFFF, 0x9B, 0x0D, &kgdt[1]);      /* code */
    init_gdt_desc(0x0, 0xFFFFF, 0x93, 0x0D, &kgdt[2]);      /* data */
    init_gdt_desc(0x0, 0x0, 0x97, 0x0D, &kgdt[3]);          /* stack */

    /* segment for user code */
    init_gdt_desc(SEGMENT_CODE_USER, 0x0, 0xFF, 0x0D, &kgdt[4]); /* ucode */
    init_gdt_desc(SEGMENT_CODE_USER, 0x0, 0xF3, 0x0D, &kgdt[5]); /* udata */
    init_gdt_desc(0x0, 0x20, 0xF7, 0x0D, &kgdt[6]); /* ustack */

    init_gdt_desc((uint32) &defaultTss, 0x67, 0xE9, 0x00, &kgdt[7]); /* tss descriptor */

    kgdtr.limite = GDTSIZE * 8;
    kgdtr.base = GDTBASE;

    memcpy((char *) kgdtr.base, (char *) kgdt, kgdtr.limite);

    asm("lgdtl (kgdtr)");

    asm("   movw $0x10, %ax \n \
       movw %ax, %ds       \n \
       movw %ax, %es       \n \
       movw %ax, %fs       \n \
       movw %ax, %gs       \n \
       ljmp $0x08, $next   \n \
       next:               \n");

    return;
}

static void initDefaultTss()
{
    defaultTss.debugFlag = 0x00;
    defaultTss.ioMapBaseAddres = 0x00;
    defaultTss.esp0 = SEGMENT_STACK_USER;
    defaultTss.ss0 = 0x18;
}
