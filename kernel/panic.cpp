#include <libraries/std/types.hpp>

void panic(const char *message, const char *file, uint32_t line)
{
    __asm__ __volatile__ ("cli\n");
    while(1);
}

void panicAssert(const char *file, uint32_t line, const char *desc)
{
    __asm__ __volatile__ ("cli\n");
    while(1);
}
