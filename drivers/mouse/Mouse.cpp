#include "Mouse.hpp"

void mouseWrite(uint8 write)
{
    outPortB(0x64, 0xD4);
    outPortB(0x60, write);
}

uint8 mouseRead()
{
    return (inPortB(0x60));
}

uint32 mouseHandler(intRegs *regs)
{
    serialPutstr((uint8 *)"mouse packet\n");
    // static uint8 status, cicle = 0;
    // static struct mouse_packet pkt;

    // status = inPortB(0x64);

    // if ((status & 0x01) && (status & 0x20))
    // {
    //     switch (cicle)
    //     {
    //     case 0:
    //         pkt.flags = mouse_read();
    //         cicle++;
    //         break;
    //     case 1:
    //         if (pkt.flags & 0x10) // is dY negative?
    //             pkt.dx = (int32)mouse_read() | 0xFFFFFF00;
    //         else
    //             pkt.dx = (int32)mouse_read();

    //         cicle++;
    //         break;
    //     case 2:

    //         if (pkt.flags & 0x20) // is dY negative?
    //             pkt.dy = (int32)mouse_read() | 0xFFFFFF00;
    //         else
    //             pkt.dy = (int32)mouse_read();

    //         if ((pkt.flags & 0x80) || (pkt.flags & 0x40) == 0)
    //         { // x/y overflow ?
    //             packet = (struct mouse_packet *)malloc(sizeof(struct mouse_packet));

    //             // if(pkt.flags & 0x20) {  // is dY negative?
    //             //   pkt.dy =
    //             // }

    //             Memory::cpy(&pkt, packet, sizeof(struct mouse_packet));

    //             queue_add(&mouse_queue, packet);
    //             wake_up(&mouse_wait);
    //         } // else { do nothing, discard entire packet :/ }
    //         // printf("mouse packet: flags=0x%x, dx=%d, dy=%d\n", pkt.flags, pkt.dx, pkt.dy);
    //         cicle = 0;
    //         break;
    //     default:
    //         cicle = 0;
    //         break;
    //     }
    // }
    // pic_acknowledge(12);
}

Mouse::Mouse()
{
    uint8 status;

    outPortB(0x64, 0xA8);
    outPortB(0x64, 0x20);

    status = (inPortB(0x60) | 2);

    outPortB(0x64, 0x60);
    outPortB(0x60, status);

    mouseWrite(0xF6);
    mouseRead();

    mouseWrite(0xF4);
    mouseRead();

    IRQ_SET_HANDLER(12, mouseHandler);
    irqEnable(12);
}
