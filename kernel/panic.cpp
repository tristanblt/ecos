#include <libraries/std/types/CTypes.hpp>

void panic(const char *message, const char *file, uint32 line)
{
    __asm__ __volatile__ ("cli\n");
    while(1);
}

void panicAssert(const char *file, uint32 line, const char *desc)
{
    __asm__ __volatile__ ("cli\n");
    while(1);
}
