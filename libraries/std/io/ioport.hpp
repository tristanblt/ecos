#include <libraries/std/types/CTypes.hpp>

void enable(void);
void disable(void);
void outPortB(uint32 port, uint8 value);
void outPortW(uint32 port, uint16 value);
void outPortL(uint32 port, uint32 value);
unsigned char inPortB(uint32 port);
uint16 inPortW(uint32 port);
uint32 inPortL(uint32 port);
