#include <libraries/std/types/CTypes.hpp>

uint8 biosReadByte(uint16 segment, uint16 offset)
{
    uint32 laddress = segment * 16 + offset;

    if ((laddress < 0x400) || (laddress > 0xFFFFE))
        return (0);
    return (((uint8 *)laddress)[0]);
}

uint16 biosReadWord(uint16 segment, uint16 offset)
{
    uint32 laddress = segment * 16 + offset;

    if ((laddress < 0x400) || (laddress > 0xFFFFE))
        return (0);
    return (((uint16 *)laddress)[0]);
}
