#ifndef _PIC_H_
#define _PIC_H_

#include <libraries/std/types.hpp>

#define IRQ_BASE 0x20

void pic(void);
void irqEnable(uint8_t irq);
void picAcknowledge(uint8_t irq);

#endif
