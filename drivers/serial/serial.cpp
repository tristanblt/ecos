#include <drivers/serial/Serial.hpp>

using namespace std;
using namespace drvs;

uint16 SERIAL_PORT[4];

void Serial::putchar(uint8 c)
{
#ifdef SERIAL_DEBUG
    IOPort::outPortB(SERIAL_PORT[0], c);
#endif
}

void Serial::putstr(uint8 *str)
{
#ifdef SERIAL_DEBUG
    for (int i = 0; str[i]; i++)
        putchar(str[i]);
#endif
}

uint32 Serial::putint(uint32 n)
{
#ifdef SERIAL_DEBUG
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    if (n >= 10) {
        putint(n / 10);
        putchar(n % 10 + '0');
    }
    if (n < 10)
        putchar(n % 10 + '0');
    return (n);
#endif
}

void Serial::init()
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
    for (i = 0; i < 4; i++)
    {
        IOPort::outPortB(SERIAL_PORT[i] + 1, 0x00);
        IOPort::outPortB(SERIAL_PORT[i] + 3, 0x80);
        IOPort::outPortB(SERIAL_PORT[i] + 0, 0x03);
        IOPort::outPortB(SERIAL_PORT[i] + 1, 0x00);
        IOPort::outPortB(SERIAL_PORT[i] + 3, 0x03);
        IOPort::outPortB(SERIAL_PORT[i] + 2, 0x7);
    }
}

void Serial::putEcosLogo()
{
    putstr((uint8 *)"\n\n");
    putstr((uint8 *)"#####  #####  #######  #####\n");
    putstr((uint8 *)"##     ##     ##   ##  ##   \n");
    putstr((uint8 *)"#####  ##     ##   ##  #####\n");
    putstr((uint8 *)"##     ##     ##   ##     ##\n");
    putstr((uint8 *)"#####  #####  #######  #####\n");
    putstr((uint8 *)"\n\nInit ECOS kernel...\n\n");
}

void Serial::putTask(uint8 *str, bool done)
{
    if (done)
    {
        putstr((uint8 *)"[done]   ");
    }
    else
    {
        putstr((uint8 *)"[start]  ");
    }
    putstr(str);
    putstr((uint8 *)"\n");
}