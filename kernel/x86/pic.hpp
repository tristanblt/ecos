#ifndef _PIC_H_
#define _PIC_H_

#include <libraries/std/types/CTypes.hpp>

#define IRQ_BASE 0x20

void pic(void);
void irqEnable(uint8 irq);
void picAcknowledge(uint8 irq);

#endif
