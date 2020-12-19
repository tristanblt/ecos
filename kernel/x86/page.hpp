#ifndef _PAGE_H_
#define _PAGE_H_

#include <libraries/std/types.hpp>

#define PAGE_FLAG_BITMAP_END (0x5 << 9)
#define PAGE_FLAG_BITMAP_START (0x2 << 9)

#define PAGE_TABLE_SIZE 0x1000
#define PAGE_TABLE_ADDR 0xFFC00000
#define PAGE_TABLE_ENTRY (PAGE_TABLE_ADDR >> 22)

#define PAGE_FLAG_PRESENT (1 << 0)
#define PAGE_FLAG_RW (1 << 1)
#define PAGE_FLAG_USER (1 << 2)

void pageMap(uint32_t pAddr, uint32_t vAddr);
void pageUnmap(uint32_t vAddr);
uint32_t pageMapUntil(uint32_t newLimit);
uint32_t pageFreeAbove(uint32_t limit);
void pageTableSet(uint32_t virtAddr, uint32_t *pgTable, uint32_t flags);

#endif
