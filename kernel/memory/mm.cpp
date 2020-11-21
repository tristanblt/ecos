#include <kernel/arch.hpp>
#include <kernel/memory/mm.hpp>

void frame_setup(uint32_t mem_size, uint32_t reserved_start, uint32_t reserved_end);

uint32_t malloc_top, heap;
mblock_t *root_mblock, *last_block;
uint32_t page_table_temp[1024] __attribute__((aligned(4096)));

static uint32_t expand(uint32_t requested_size) {
  return (page_map_until(malloc_top + requested_size));
}

mblock_t *_split_hole(mblock_t *b, uint32_t size)
{
    mblock_t *new_hole;

    if (!b->hole)
        return (nullptr);
    if ((b->size - (size + sizeof(mblock_t))) < (sizeof(mblock_t))) {
        b->hole = 0;
        return b;
    }
    else {
        new_hole = (mblock_t *)(b->addr + size);
        new_hole->magic = MBLOCK_MAGIC;
        new_hole->hole = 1;
        new_hole->size = b->size - sizeof(mblock_t) - size;
        new_hole->addr = (b->addr + size + sizeof(mblock_t));
        b->hole = 0;
        b->size = size;

        new_hole->next = b->next;
        b->next = new_hole;

        return b;
    }
}

mblock_t *_find_hole(uint32_t size)
{
    mblock_t *b;

    b = root_mblock;
    while (b) {
        if (b->magic == MBLOCK_MAGIC) {
            if (b->hole) {
                if (b->size >= size)
                    return _split_hole(b, size);
            }
        }
        else
            PANIC("mblock with wrong magic");
        b = b->next;
    }
    return (nullptr);
}

void *malloc(uint32_t size)
{
    mblock_t *b;
    uint32_t new_heap;

    if (size == 0)
        return (nullptr);
    b = _find_hole(size);
    if (b)
        return (void *)b->addr;
    if ((malloc_top + size + sizeof(mblock_t)) > heap) {
        new_heap = expand(size);
        if(new_heap == heap)
          return (nullptr);
        heap = new_heap;
    }
    b = (mblock_t *)malloc_top;
    b->hole = 0;
    b->magic = MBLOCK_MAGIC;
    b->size = size;
    b->addr = malloc_top + sizeof(mblock_t);
    b->next = nullptr;
    last_block->next = b;
    last_block = b;
    malloc_top = (uint32_t)(b->addr + b->size);
    return ((uint32_t *)b->addr);
}

void mm(multiboot_info_t *mb)
{
    multiboot_module_t *mod;
    uint32_t p_addr, p_addr_max, v_addr;
    uint32_t i = 0, heap = 0, ld_kernel_limit;

    ld_kernel_limit = (uint32_t)&kernel_vaddr_end;
    if (ld_kernel_limit == 0)
        PANIC("ld script's invalid Kernel limit");
    heap = ld_kernel_limit;
    mod = (multiboot_module_t *)mb->mods_addr;
    for (i = 0; i < mb->mods_count; i++)
    {
        if ((KERNEL_BASE + mod->mod_end - 0x100000) > heap)
            heap = KERNEL_BASE + mod->mod_end - 0x100000;
    }
    frame_setup(mb->mem_upper * 1024, 0, heap - KERNEL_BASE + 0x100000);
    p_addr = 0x100000;
    p_addr_max = ((heap - KERNEL_BASE + 0x100000) & 0xFFFFF000) + 0x1000;
    v_addr = KERNEL_BASE;
    for (; p_addr < p_addr_max; p_addr += 0x1000, v_addr += 0x1000)
        page_map(p_addr, v_addr);
    malloc_top = heap;
    heap = (heap & 0xFFFFF000) + 0x1000;
    root_mblock = (mblock_t *)malloc_top;
    root_mblock->hole = 0;
    root_mblock->magic = MBLOCK_MAGIC;
    root_mblock->size = 1;
    root_mblock->addr = malloc_top + sizeof(mblock_t);
    root_mblock->next = nullptr;
    malloc_top = (uint32_t)(root_mblock->addr + root_mblock->size);
    last_block = root_mblock;
}