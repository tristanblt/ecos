#include <kernel/arch.hpp>
#include <kernel/multiboot.hpp>
#include <libraries/std/io/ioport.hpp>
#include <kernel/memory/mm.hpp>
#include <drivers/vesa/VbeVideoMode.hpp>
#include <drivers/serial/serial.hpp>
#include <drivers/mouse/Mouse.hpp>

// uint32_t kernel_stack_addr;

extern "C" int kmain(uint32_t multiboot_info)
{
    disable();
    arch();
    mm((multiboot_info_t *)multiboot_info);

    serial();

    serial_putstr((uint8_t *)"Welcome to ECOS\n");

    Mouse m;

    VbeVideoMode vesa;
    vesa.init();

    uint32_t i = 0;
    while (true) {
        vesa.draw_rect({0, 0, 1600, 900}, (color_t){0xA0A0A0});
        vesa.draw_rect({100 + i, 100, 500, 500}, (color_t){0xFFFFFF});
        i+=10;
        vesa.display();
    }
}