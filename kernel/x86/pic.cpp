#include <libraries/std/io/IOPort.hpp>

using namespace std;

#define PIC_MASTER_CTRL 0x20
#define PIC_MASTER_DATA 0x21
#define PIC_SLAVE_CTRL 0xA0
#define PIC_SLAVE_DATA 0xA1

void pic(void)
{
    // ICW1
    IOPort::outPortB(PIC_MASTER_CTRL, 0x11); // init master PIC
    IOPort::outPortB(PIC_SLAVE_CTRL, 0x11);  // init slave PIC
    // ICW2
    IOPort::outPortB(PIC_MASTER_DATA, 0x20); // IRQ 0..7 remaped to 0x20..0x27
    IOPort::outPortB(PIC_SLAVE_DATA, 0x28);  // IRQ 8..15 remaped to 0x28..0x37
    // ICW3
    IOPort::outPortB(PIC_MASTER_DATA, 0x04); // set as Master
    IOPort::outPortB(PIC_SLAVE_DATA, 0x02);  // set as Slave
    // ICW4
    IOPort::outPortB(PIC_MASTER_DATA, 0x01); // set x86 mode
    IOPort::outPortB(PIC_SLAVE_DATA, 0x01);  // set x86 mode

    IOPort::outPortB(PIC_MASTER_DATA, 0xFF); // all interrupts IOPort::disabled
    IOPort::outPortB(PIC_SLAVE_DATA, 0xFF);

    __asm__ __volatile__("nop");
}

static uint16 ocw1 = 0xFFFB;

void irqEnable(uint8 irq)
{
    ocw1 &= (uint16) ~((1 << irq));

    if (irq < 8)
        IOPort::outPortB(PIC_MASTER_DATA, (uint8)(ocw1 & 0xFF));
    else
        IOPort::outPortB(PIC_SLAVE_DATA, (uint8)(ocw1 >> 8));
}

void picAcknowledge(uint8 irq)
{
    if (irq > 7)
        IOPort::outPortB(PIC_SLAVE_CTRL, 0x20);
    IOPort::outPortB(PIC_MASTER_CTRL, 0x20);
}
