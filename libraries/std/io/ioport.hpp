#include <libraries/std/types.hpp>

void enable(void);
void disable(void);
void outPortB(uint32_t port, uint8_t value);
void outPortW(uint32_t port, uint16_t value);
void outPortL(uint32_t port, uint32_t value);
unsigned char inPortB(uint32_t port);
uint16_t inPortW(uint32_t port);
uint32_t inPortL(uint32_t port);
