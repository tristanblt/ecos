#ifndef _BIOS_H_
#define _BIOS_H_

#include <libraries/std/types.hpp>

uint8_t biosReadByte(uint16_t segment, uint16_t offset);
uint16_t biosReadWord(uint16_t segment, uint16_t offset);

#endif
