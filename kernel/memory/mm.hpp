#ifndef _MM_H_
#define _MM_H_

#include <kernel/multiboot.hpp>

#define USER_STACK_BASE 0xBF800000
#define USER_STACK_SIZE 0x1000
#define USER_BASE 0x01000000
#define KERNEL_BASE 0xC0000000
#define KERNEL_LIMIT 0xDFFF0000 // used for video memory

#define FRAME_SIZE 0x1000

#define MBLOCK_MAGIC 0xF4283F30 // thanks https://www.browserling.com/tools/random-hex

typedef struct mblock
{
    uint32_t magic;
    uint32_t hole;
    uint32_t size;
    uint32_t addr;
    struct mblock *next;
} mblock_t __attribute__((packed));

// from Linker script
extern uint8_t kernelPaddrStart;
extern uint8_t kernelPaddrEnd;
extern uint8_t kernelVaddrStart;
extern uint8_t kernelVaddrEnd;

#define VIRTUAL_TO_PHYSICAL(addr) ((uint32_t)addr - (uint32_t)&kernelVaddrStart + (uint32_t)&kernelPaddrStart)

void mm(multiboot_info_t *mb);

#endif
