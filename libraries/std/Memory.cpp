#include <libraries/std/types/CTypes.hpp>
#include <libraries/std/Memory.hpp>

using namespace std;

void Memory::cpy8(void *src, void *dst, uint32 size)
{
    uint32 i = 0;

    for (; i < size; i++)
        ((uint8 *)dst)[i] = ((uint8 *)src)[i];
}

void Memory::cpy32(void *src, void *dst, uint32 size)
{
    uint32 i = 0;

    for (; i < size; i++)
        ((uint32 *)dst)[i] = ((uint32 *)src)[i];
}

void *Memory::set8(void *dest, uint8 val, uint32 len)
{
    uint8 *ptr = (uint8 *)dest;

    while (len-- > 0)
        *ptr++ = val;
    return (dest);
}

void *Memory::set32(void *dest, uint32 val, uint32 len)
{
    uint32 *ptr = (uint32 *)dest;

    while (len-- > 0)
        *ptr++ = val;
    return (dest);
}