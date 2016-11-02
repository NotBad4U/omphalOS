#include "gdt.h"

struct gdtdesc kgdt[GDTSIZE];	/* GDT with GDTSIZE segment */
struct gdtr kgdtr;              /* GDTR */


void init_gdt_desc(uint32 base, uint32 limite, uint8 acces, uint8 other, struct gdtdesc *desc)
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


void init_gdt()
{
    init_gdt_desc(0x0, 0x0, 0x0, 0x0, &kgdt[0]);
    init_gdt_desc(0x0, 0xFFFFF, 0x9B, 0x0D, &kgdt[1]);      /* code */
    init_gdt_desc(0x0, 0xFFFFF, 0x93, 0x0D, &kgdt[2]);      /* data */
    init_gdt_desc(0x0, 0x0, 0x97, 0x0D, &kgdt[3]);          /* stack */

    kgdtr.limite = GDTSIZE * 8;
    kgdtr.base = GDTBASE;

    memory_copy((char *) kgdtr.base, (char *) kgdt, kgdtr.limite);

    asm("lgdtl (kgdtr)");

    asm("   movw $0x10, %ax \n \
       movw %ax, %ds       \n \
       movw %ax, %es       \n \
       movw %ax, %fs       \n \
       movw %ax, %gs       \n \
       ljmp $0x08, $next   \n \
       next:		\n");
}
