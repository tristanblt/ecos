#include <libraries/std/types/CTypes.hpp>
#include <drivers/serial/Serial.hpp>

void panic(const char *message, const char *file, uint32 line)
{
    drvs::Serial::putstr((uint8 *) "[PANIC] ");
    drvs::Serial::putstr((uint8 *) file);
    drvs::Serial::putstr((uint8 *) ":");
    drvs::Serial::putint(line);
    drvs::Serial::putstr((uint8 *) " -> ");
    drvs::Serial::putstr((uint8 *) message);
    drvs::Serial::putstr((uint8 *) "\n");
    __asm__ __volatile__ ("cli\n");
    while(1);
}

void panicAssert(const char *file, uint32 line, const char *desc)
{
    __asm__ __volatile__ ("cli\n");
    while(1);
}
