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

void page_map(uint32_t p_addr, uint32_t v_addr);
void page_unmap(uint32_t v_addr);
uint32_t page_map_until(uint32_t new_limit);
uint32_t page_free_above(uint32_t limit);
void page_table_set(uint32_t virt_addr, uint32_t *pg_table, uint32_t flags);

#endif
