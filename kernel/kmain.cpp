#include <kernel/arch.hpp>
#include <kernel/multiboot.hpp>
#include <libraries/std/io/ioport.hpp>
#include <kernel/memory/mm.hpp>
#include <drivers/vesa/VbeVideoMode.hpp>
#include <drivers/serial/serial.hpp>
#include <drivers/mouse/Mouse.hpp>
#include <libraries/ecs/Ecos.hpp>

void initEcos(ecs::Ecos *ecos)
{

}

extern "C" int kmain(uint32 multiboot_info)
{
    disable();
    arch();
    mm((multiboot_info_t *)multiboot_info);
    serial();

    serialPutstr((uint8 *)"\n\n");
    serialPutstr((uint8 *)"#####  #####  #######  #####\n");
    serialPutstr((uint8 *)"##     ##     ##   ##  ##   \n");
    serialPutstr((uint8 *)"#####  ##     ##   ##  #####\n");
    serialPutstr((uint8 *)"##     ##     ##   ##     ##\n");
    serialPutstr((uint8 *)"#####  #####  #######  #####\n");
    serialPutstr((uint8 *)"\n\nInit OS...\n");

    serialPutstr((uint8 *)"-> Init VESA mode\n");
    VbeVideoMode vesa;
    vesa.init();

    serialPutstr((uint8 *)"-> Init ECS environnement\n");
    ecs::Ecos ecos;

    initEcos(&ecos);

    serialPutstr((uint8 *)"-> Run ECOS\n");
    ecos.run();
}