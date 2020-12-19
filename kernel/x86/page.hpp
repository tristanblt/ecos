#ifndef _PAGE_H_
#define _PAGE_H_

#include <libraries/std/types/CTypes.hpp>

#define PAGE_FLAG_BITMAP_END (0x5 << 9)
#define PAGE_FLAG_BITMAP_START (0x2 << 9)

#define PAGE_TABLE_SIZE 0x1000
#define PAGE_TABLE_ADDR 0xFFC00000
#define PAGE_TABLE_ENTRY (PAGE_TABLE_ADDR >> 22)

#define PAGE_FLAG_PRESENT (1 << 0)
#define PAGE_FLAG_RW (1 << 1)
#define PAGE_FLAG_USER (1 << 2)

void pageMap(uint32 pAddr, uint32 vAddr);
void pageUnmap(uint32 vAddr);
uint32 pageMapUntil(uint32 newLimit);
uint32 pageFreeAbove(uint32 limit);
void pageTableSet(uint32 virtAddr, uint32 *pgTable, uint32 flags);

#endif
