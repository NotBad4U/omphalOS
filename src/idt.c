#include "idt.h"
#include "util.h"
#include "system.h"

idtDesc_t idt[IDTSIZE];
idtr_t idtr;

void setIdtDesc(int n, uint32 handler)
{
    idt[n].lowOffset = low_16(handler);
    idt[n].select = KERNEL_CS;
    idt[n].always0 = 0;
    idt[n].flags = 0b10001110;
    idt[n].highOffset = high_16(handler);
}

void initIdtr()
{
    idtr.base = IDTBASE;
    idtr.limit = IDTSIZE * sizeof(idtDesc_t) - 1;
    asm("lidtl (idtr)");
}

void initPic()
{
	/* Initialization of ICW1 (port 0x20 / port 0xA0) */
	outportb(0x20, 0x11);
	outportb(0xA0, 0x11);

	/* Initialization of ICW2  (port 0x21 / port 0xA1) */
	outportb(0x21, 0x20); //Master start vector 32
	outportb(0xA1, 0x70); //Slave start vector 96

	/* ICW3  (port 0x21 / port 0xA1) */
	outportb(0x21, 0x04);
	outportb(0xA1, 0x02);

	/* ICW4 (port 0x21 / port 0xA1) */
	outportb(0x21, 0x01);
	outportb(0xA1, 0x01);

	/* IMR (Interrupt Mask Register) */
	outportb(0x21, 0x0);
	outportb(0xA1, 0x0);
}
