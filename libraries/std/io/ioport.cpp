#include "ioport.hpp"

void enable(void)
{
    __asm__ __volatile__("sti");
}

void disable(void)
{
    __asm__ __volatile__("cli");
}

void outPortB(uint32 port, uint8 value)
{
	__asm__ __volatile__("outb %%al,%%dx"::"d" (port), "a" (value));
}

void outPortW(uint32 port, uint16 value)
{
	__asm__ __volatile__("outw %%ax,%%dx"::"d" (port), "a" (value));
}

void outPortL(uint32 port, uint32 value)
{
	__asm__ __volatile__("outl %%eax,%%dx"::"d" (port), "a" (value));
}

unsigned char inPortB(uint32 port)
{
	uint8 ret;

	__asm__ __volatile__("inb %%dx,%%al":"=a" (ret):"d"(port));
	return (ret);
}

uint16 inPortW(uint32 port)
{
	uint16 ret;

	__asm__ __volatile__("inw %%dx,%%ax":"=a" (ret):"d"(port));
	return (ret);
}

uint32 inPortL(uint32 port)
{
	uint32 ret;

	__asm__ __volatile__("inl %%dx,%%eax":"=a" (ret):"d"(port));
	return (ret);
}
