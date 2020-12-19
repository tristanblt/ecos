#include "arch.hpp"
#include <kernel/memory/mm.hpp>

uint32 frameGet();
uint32 frameFree(uint32 addr);

void pageMap(uint32 pAddr, uint32 vAddr)
{
    uint32 *pd, *table, pIdx, tIdx;

    __asm__ __volatile__("movl %%cr3, %%eax; movl %%eax, %0;":"=m"(pd)::"%eax");
    pd = (uint32 *)((uint32)pd & 0xFFFFF000);
    tIdx = vAddr >> 22;
    if ((pd[tIdx] & 0xFFFFF000) == 0)
        pd[tIdx] = frameGet();
    pd[tIdx] = pd[tIdx] | PAGE_FLAG_PRESENT | PAGE_FLAG_RW;
    table = (uint32 *)(pd[tIdx] & 0xFFFFF000);
    pIdx = (vAddr >> 12) & 0x3FF;
    table[pIdx] = (pAddr & 0xFFFFF000) | PAGE_FLAG_PRESENT | PAGE_FLAG_RW;
}

void pageUnmap(uint32 vAddr)
{
    uint32 *pd, *table, pIdx, tIdx;

    __asm__ __volatile__("movl %%cr3, %%eax; movl %%eax, %0;":"=m"(pd)::"%eax");
    pd = (uint32 *)((uint32)pd & 0xFFFFF000);
    tIdx = vAddr >> 22;
    pd[tIdx] = pd[tIdx] | PAGE_FLAG_PRESENT | PAGE_FLAG_RW;
    table = (uint32 *)(pd[tIdx] & 0xFFFFF000);
    pIdx = (vAddr >> 12) & 0x3FF;
    frameFree(table[pIdx] & 0xFFFFF000);
    table[pIdx] = 0;
}

uint32 pageUpper() {
    uint32 *pd, *table, pIdx, tIdx, vAddr;

    __asm__ __volatile__("movl %%cr3, %%eax; movl %%eax, %0;":"=m"(pd)::"%eax");
    pd = (uint32 *)((uint32)pd & 0xFFFFF000);
    vAddr = KERNEL_BASE;
    for (vAddr = KERNEL_BASE; vAddr < KERNEL_LIMIT; vAddr += 0x1000) {
        tIdx = vAddr >> 22;
        table = (uint32 *)(pd[tIdx] & 0xFFFFF000);
        pIdx = (vAddr >> 12) & 0x3FF;
        if (table[pIdx] == 0)
            return (vAddr - 0x1000);
    }
    return (vAddr - 0x1000);
}

uint32 pageMapUntil(uint32 newLimit)
{
    uint32 oldLimit, pAddr;

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

uint32 pageFreeAbove(uint32 limit)
{
    uint32 newPageLimit, pageLimit;

    newPageLimit = (limit & 0xFFFFF000) + 0x1000;
    pageLimit = pageUpper();
    while (newPageLimit <= pageLimit) {
        pageUnmap(newPageLimit);
        newPageLimit += 0x1000;
    }
    return (newPageLimit);
}

void pageTableSet(uint32 virtAddr, uint32 *pgTable, uint32 flags)
{
    uint32 *pd;

    __asm__ __volatile__("movl %%cr3, %%eax; movl %%eax, %0;":"=m"(pd)::"%eax");
    pd[virtAddr >> 22] = (uint32)pgTable | flags;
}
