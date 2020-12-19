#ifndef _BIOS_H_
#define _BIOS_H_

#include <libraries/std/types/CTypes.hpp>

uint8 biosReadByte(uint16 segment, uint16 offset);
uint16 biosReadWord(uint16 segment, uint16 offset);

#endif
