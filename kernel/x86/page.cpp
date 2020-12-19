#include "arch.hpp"
#include <kernel/memory/mm.hpp>

uint32_t frameGet();
uint32_t frameFree(uint32_t addr);

void pageMap(uint32_t pAddr, uint32_t vAddr)
{
    uint32_t *pd, *table, pIdx, tIdx;

    __asm__ __volatile__("movl %%cr3, %%eax; movl %%eax, %0;":"=m"(pd)::"%eax");
    pd = (uint32_t *)((uint32_t)pd & 0xFFFFF000);
    tIdx = vAddr >> 22;
    if ((pd[tIdx] & 0xFFFFF000) == 0)
        pd[tIdx] = frameGet();
    pd[tIdx] = pd[tIdx] | PAGE_FLAG_PRESENT | PAGE_FLAG_RW;
    table = (uint32_t *)(pd[tIdx] & 0xFFFFF000);
    pIdx = (vAddr >> 12) & 0x3FF;
    table[pIdx] = (pAddr & 0xFFFFF000) | PAGE_FLAG_PRESENT | PAGE_FLAG_RW;
}

void pageUnmap(uint32_t vAddr)
{
    uint32_t *pd, *table, pIdx, tIdx;

    __asm__ __volatile__("movl %%cr3, %%eax; movl %%eax, %0;":"=m"(pd)::"%eax");
    pd = (uint32_t *)((uint32_t)pd & 0xFFFFF000);
    tIdx = vAddr >> 22;
    pd[tIdx] = pd[tIdx] | PAGE_FLAG_PRESENT | PAGE_FLAG_RW;
    table = (uint32_t *)(pd[tIdx] & 0xFFFFF000);
    pIdx = (vAddr >> 12) & 0x3FF;
    frameFree(table[pIdx] & 0xFFFFF000);
    table[pIdx] = 0;
}

uint32_t pageUpper() {
    uint32_t *pd, *table, pIdx, tIdx, vAddr;

    __asm__ __volatile__("movl %%cr3, %%eax; movl %%eax, %0;":"=m"(pd)::"%eax");
    pd = (uint32_t *)((uint32_t)pd & 0xFFFFF000);
    vAddr = KERNEL_BASE;
    for (vAddr = KERNEL_BASE; vAddr < KERNEL_LIMIT; vAddr += 0x1000) {
        tIdx = vAddr >> 22;
        table = (uint32_t *)(pd[tIdx] & 0xFFFFF000);
        pIdx = (vAddr >> 12) & 0x3FF;
        if (table[pIdx] == 0)
            return (vAddr - 0x1000);
    }
    return (vAddr - 0x1000);
}

uint32_t pageMapUntil(uint32_t newLimit)
{
    uint32_t oldLimit, pAddr;

    oldLimit = pageUpper() + 0x1000;
    newLimit &= 0xFFFFF000;
    while (oldLimit <= newLimit) {
        pAddr = frameGet();
        if (!pAddr)
            return (oldLimit);
        pageMap(pAddr, oldLimit);
        oldLimit += 0x1000;
    }
    return (newLimit + 0x1000);
}

uint32_t pageFreeAbove(uint32_t limit)
{
    uint32_t newPageLimit, pageLimit;

    newPageLimit = (limit & 0xFFFFF000) + 0x1000;
    pageLimit = pageUpper();
    while (newPageLimit <= pageLimit) {
        pageUnmap(newPageLimit);
        newPageLimit += 0x1000;
    }
    return (newPageLimit);
}

void pageTableSet(uint32_t virtAddr, uint32_t *pgTable, uint32_t flags)
{
    uint32_t *pd;

    __asm__ __volatile__("movl %%cr3, %%eax; movl %%eax, %0;":"=m"(pd)::"%eax");
    pd[virtAddr >> 22] = (uint32_t)pgTable | flags;
}
