#include <libraries/std/types.hpp>

uint8_t bios_read_byte(uint16_t segment, uint16_t offset)
{
    uint32_t laddress = segment * 16 + offset;

    if ((laddress < 0x400) || (laddress > 0xFFFFE))
        return (0);
    return (((uint8_t *)laddress)[0]);
}

uint16_t bios_read_word(uint16_t segment, uint16_t offset)
{
    uint32_t laddress = segment * 16 + offset;

    if ((laddress < 0x400) || (laddress > 0xFFFFE))
        return (0);
    return (((uint16_t *)laddress)[0]);
}
