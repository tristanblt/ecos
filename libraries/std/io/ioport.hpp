#include <libraries/std/types.hpp>

void enable(void);
void disable(void);
void outportb(uint32_t port, uint8_t value);
void outportw(uint32_t port, uint16_t value);
void outportl(uint32_t port, uint32_t value);
unsigned char inportb(uint32_t port);
uint16_t inportw(uint32_t port);
uint32_t inportl(uint32_t port);
