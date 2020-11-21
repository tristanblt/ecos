#include <kernel/arch.hpp>
#include <kernel/multiboot.hpp>
#include <kernel/ioport.hpp>
#include <kernel/mm.hpp>
#include <drivers/vesa/VbeVideoMode.hpp>

// uint32_t kernel_stack_addr;

extern "C" int kmain(uint32_t multiboot_info)
{
    multiboot_info_t *mbinfo = (multiboot_info_t *) multiboot_info;

    disable();
    arch();
    mm(mbinfo);

    VbeVideoMode vesa;
    vesa.init();
    vesa.draw_rect({100, 100, 100, 100}, (color_t){0xFF0000});
    vesa.draw_rect({100, 210, 100, 100}, (color_t){0xFF0000});
    vesa.draw_rect({180, 160, 700, 100}, (color_t){0xFF0000});
    vesa.draw_rect({880, 150, 120, 120}, (color_t){0xFF0000});
}