#include <libraries/std/types.hpp>
#include <libraries/std/io/ioport.hpp>
#include <kernel/devices/bios.hpp>

uint16_t SERIAL_PORT[4];

void serial_putchar(uint8_t c)
{
    outportb(SERIAL_PORT[0], c);
}

void serial_putstr(uint8_t *str)
{
    for (int i = 0; str[i]; i++)
        outportb(SERIAL_PORT[0], str[i]);
}

void serial()
{
    uint32_t i;

    if ((SERIAL_PORT[0] = bios_read_word(0x40, 0x0)) == 0)
        SERIAL_PORT[0] = 0x3F8;
    if ((SERIAL_PORT[1] = bios_read_word(0x40, 0x2)) == 0)
        SERIAL_PORT[1] = 0x2F8;
    if ((SERIAL_PORT[2] = bios_read_word(0x40, 0x4)) == 0)
        SERIAL_PORT[2] = 0x3E8;
    if ((SERIAL_PORT[3] = bios_read_word(0x40, 0x6)) == 0)
        SERIAL_PORT[3] = 0x2E8;
    for (i = 0; i < 4; i++) {
        outportb(SERIAL_PORT[i] + 1, 0x00);
        outportb(SERIAL_PORT[i] + 3, 0x80);
        outportb(SERIAL_PORT[i] + 0, 0x03);
        outportb(SERIAL_PORT[i] + 1, 0x00);
        outportb(SERIAL_PORT[i] + 3, 0x03);
        outportb(SERIAL_PORT[i] + 2, 0x7);
    }
}
