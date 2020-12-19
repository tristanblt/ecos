#include "arch.hpp"
#include <kernel/memory/mm.hpp>

struct gdtEntry gdtEntries[6];
struct gdt gdtr;

void tss();
extern "C" void loadGdt(struct gdt *);
extern "C" void loadTss();

void gdtEntrySetup(struct gdtEntry *gdte, uint32_t base, uint32_t limit,
                     uint32_t access, uint32_t flags);

void gdt()
{
    tss();

    gdtEntrySetup(&(gdtEntries[0]), 0x00000000, 0x00000000, 0x00, 0x0); // null descriptor
    gdtEntrySetup(&(gdtEntries[1]), 0x00000000, 0xFFFFFFFF, 0x9A, 0xC); // kernel code
    gdtEntrySetup(&(gdtEntries[2]), 0x00000000, 0xFFFFFFFF, 0x92, 0xC); // kernel data
    gdtEntrySetup(&(gdtEntries[3]), 0x00000000, 0xFFFFFFFF, 0xFA, 0xC); // user code
    gdtEntrySetup(&(gdtEntries[4]), 0x00000000, 0xFFFFFFFF, 0xF2, 0xC); // user data
    gdtEntrySetup(&(gdtEntries[5]), VIRTUAL_TO_PHYSICAL(&tss), sizeof(tssEntry_t), 0x89, 0xC);

    gdtr.size = 8 * 6;
    gdtr.offset = (uint32_t)&gdtEntries[0];

    loadGdt(&gdtr);
    loadTss();
}

void gdtEntrySetup(struct gdtEntry *gdte, uint32_t base, uint32_t limit,
                     uint32_t access, uint32_t flags)
{

    gdte->low = base & 0xFFFF;
    gdte->low <<= 16;
    gdte->low |= limit & 0xFFFF;

    gdte->high = ((base >> 16) & 0xFF) | ((access & 0xFF) << 8) |
                 (((limit >> 16) & 0xF) << 16) | ((flags & 0xF) << 20) |
                 (((base >> 24) & 0xFF) << 24);
}
