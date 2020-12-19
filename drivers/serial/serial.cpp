#include <libraries/std/types/CTypes.hpp>
#include <libraries/std/io/ioport.hpp>
#include <kernel/devices/bios.hpp>

uint16 SERIAL_PORT[4];

void serialPutchar(uint8 c)
{
    outPortB(SERIAL_PORT[0], c);
}

void serialPutstr(uint8 *str)
{
    for (int i = 0; str[i]; i++)
        outPortB(SERIAL_PORT[0], str[i]);
}

void serial()
{
    uint32 i;

    if ((SERIAL_PORT[0] = biosReadWord(0x40, 0x0)) == 0)
        SERIAL_PORT[0] = 0x3F8;
    if ((SERIAL_PORT[1] = biosReadWord(0x40, 0x2)) == 0)
        SERIAL_PORT[1] = 0x2F8;
    if ((SERIAL_PORT[2] = biosReadWord(0x40, 0x4)) == 0)
        SERIAL_PORT[2] = 0x3E8;
    if ((SERIAL_PORT[3] = biosReadWord(0x40, 0x6)) == 0)
        SERIAL_PORT[3] = 0x2E8;
    for (i = 0; i < 4; i++) {
        outPortB(SERIAL_PORT[i] + 1, 0x00);
        outPortB(SERIAL_PORT[i] + 3, 0x80);
        outPortB(SERIAL_PORT[i] + 0, 0x03);
        outPortB(SERIAL_PORT[i] + 1, 0x00);
        outPortB(SERIAL_PORT[i] + 3, 0x03);
        outPortB(SERIAL_PORT[i] + 2, 0x7);
    }
}
