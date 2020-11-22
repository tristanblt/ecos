/*
** EPITECH PROJECT, 2020
** ECOS
** File description:
** Mouse
*/

#include "Mouse.hpp"

void mouse_write(uint8_t write)
{
    outportb(0x64, 0xD4);
    outportb(0x60, write);
}

uint8_t mouse_read()
{
    return (inportb(0x60));
}

uint32_t mouse_handler(int_regs_t *regs)
{
    serial_putstr((uint8_t *)"mouse packet\n");
    // static uint8_t status, cicle = 0;
    // static struct mouse_packet pkt;

    // status = inportb(0x64);

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
    //             pkt.dx = (int32_t)mouse_read() | 0xFFFFFF00;
    //         else
    //             pkt.dx = (int32_t)mouse_read();

    //         cicle++;
    //         break;
    //     case 2:

    //         if (pkt.flags & 0x20) // is dY negative?
    //             pkt.dy = (int32_t)mouse_read() | 0xFFFFFF00;
    //         else
    //             pkt.dy = (int32_t)mouse_read();

    //         if ((pkt.flags & 0x80) || (pkt.flags & 0x40) == 0)
    //         { // x/y overflow ?
    //             packet = (struct mouse_packet *)malloc(sizeof(struct mouse_packet));

    //             // if(pkt.flags & 0x20) {  // is dY negative?
    //             //   pkt.dy =
    //             // }

    //             memcpy(&pkt, packet, sizeof(struct mouse_packet));

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
    uint8_t status;

    outportb(0x64, 0xA8);
    outportb(0x64, 0x20);

    status = (inportb(0x60) | 2);

    outportb(0x64, 0x60);
    outportb(0x60, status);

    mouse_write(0xF6);
    mouse_read();

    mouse_write(0xF4);
    mouse_read();

    IRQ_SET_HANDLER(12, mouse_handler);
    irq_enable(12);
}
