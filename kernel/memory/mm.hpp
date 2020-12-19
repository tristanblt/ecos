#ifndef _MM_H_
#define _MM_H_

#include <kernel/multiboot.hpp>
#include <kernel/arch.hpp>

#define USER_STACK_BASE 0xBF800000
#define USER_STACK_SIZE 0x1000
#define USER_BASE 0x01000000
#define KERNEL_BASE 0xC0000000
#define KERNEL_LIMIT 0xDFFF0000 // used for video memory

#define FRAME_SIZE 0x1000

#define MBLOCK_MAGIC 0xF4283F30

struct __attribute__((packed)) mblock
{
    uint32 magic;
    uint32 hole;
    uint32 size;
    uint32 addr;
    struct mblock *next;
};

// from Linker script
extern uint8 kernelPaddrStart;
extern uint8 kernelPaddrEnd;
extern uint8 kernelVaddrStart;
extern uint8 kernelVaddrEnd;

#define VIRTUAL_TO_PHYSICAL(addr) ((uint32)addr - (uint32)&kernelVaddrStart + (uint32)&kernelPaddrStart)

void mm(multiboot_info *mb);

#endif
