#include <kernel/arch.hpp>
#include <kernel/memory/mm.hpp>

void frameSetup(uint32 memSize, uint32 reservedStart, uint32 reservedEnd);

uint32 mallocTop, heap;
mblock *rootMblock, *lastBlock;
uint32 pageTableTemp[1024] __attribute__((aligned(4096)));

static uint32 expand(uint32 requestedSize) {
  return (pageMapUntil(mallocTop + requestedSize));
}

mblock *splitHole(mblock *b, uint32 size)
{
    mblock *newHole;

    if (!b->hole)
        return (nullptr);
    if ((b->size - (size + sizeof(mblock))) < (sizeof(mblock))) {
        b->hole = 0;
        return b;
    }
    else {
        newHole = (mblock *)(b->addr + size);
        newHole->magic = MBLOCK_MAGIC;
        newHole->hole = 1;
        newHole->size = b->size - sizeof(mblock) - size;
        newHole->addr = (b->addr + size + sizeof(mblock));
        b->hole = 0;
        b->size = size;

        newHole->next = b->next;
        b->next = newHole;

        return b;
    }
}

mblock *_find_hole(uint32 size)
{
    mblock *b;

    b = rootMblock;
    while (b) {
        if (b->magic == MBLOCK_MAGIC) {
            if (b->hole) {
                if (b->size >= size)
                    return splitHole(b, size);
            }
        }
        else
            PANIC("mblock with wrong magic");
        b = b->next;
    }
    return (nullptr);
}

void *malloc(uint32 size)
{
    mblock *b;
    uint32 newHeap;

    if (size == 0)
        return (nullptr);
    b = _find_hole(size);
    if (b)
        return (void *)b->addr;
    if ((mallocTop + size + sizeof(mblock)) > heap) {
        newHeap = expand(size);
        if(newHeap == heap)
          return (nullptr);
        heap = newHeap;
    }
    b = (mblock *)mallocTop;
    b->hole = 0;
    b->magic = MBLOCK_MAGIC;
    b->size = size;
    b->addr = mallocTop + sizeof(mblock);
    b->next = nullptr;
    lastBlock->next = b;
    lastBlock = b;
    mallocTop = (uint32)(b->addr + b->size);
    return ((uint32 *)b->addr);
}

void mm(multiboot_info_t *mb)
{
    multiboot_module_t *mod;
    uint32 pAddr, pAddrMax, vAddr;
    uint32 i = 0, heap = 0, ldKernelLimit;

    ldKernelLimit = (uint32)&kernelVaddrEnd;
    if (ldKernelLimit == 0)
        PANIC("ld script's invalid Kernel limit");
    heap = ldKernelLimit;
    mod = (multiboot_module_t *)mb->mods_addr;
    for (i = 0; i < mb->mods_count; i++)
    {
        if ((KERNEL_BASE + mod->mod_end - 0x100000) > heap)
            heap = KERNEL_BASE + mod->mod_end - 0x100000;
    }
    frameSetup(mb->mem_upper * 1024, 0, heap - KERNEL_BASE + 0x100000);
    pAddr = 0x100000;
    pAddrMax = ((heap - KERNEL_BASE + 0x100000) & 0xFFFFF000) + 0x1000;
    vAddr = KERNEL_BASE;
    for (; pAddr < pAddrMax; pAddr += 0x1000, vAddr += 0x1000)
        pageMap(pAddr, vAddr);
    mallocTop = heap;
    heap = (heap & 0xFFFFF000) + 0x1000;
    rootMblock = (mblock *)mallocTop;
    rootMblock->hole = 0;
    rootMblock->magic = MBLOCK_MAGIC;
    rootMblock->size = 1;
    rootMblock->addr = mallocTop + sizeof(mblock);
    rootMblock->next = nullptr;
    mallocTop = (uint32)(rootMblock->addr + rootMblock->size);
    lastBlock = rootMblock;
}