#include <kernel/arch.hpp>
#include <kernel/multiboot.hpp>
#include <libraries/std/io/IOPort.hpp>
#include <kernel/memory/mm.hpp>
#include <drivers/vesa/VbeVideoMode.hpp>
#include <drivers/serial/Serial.hpp>
#include <libraries/ecs/Ecos.hpp>

using namespace std;
using namespace ecs;
using namespace drvs;

void initEcos(Ecos *ecos)
{
    ecos->addSystem(nullptr);

    Entity *e = ecos->addEntity();
    e->addComponent();

    e = ecos->addEntity();
    e->addComponent();
}

extern "C" int kmain(uint32 multiboot_info)
{
    IOPort::disable();
    arch();


    Serial::init();
    Serial::putEcosLogo();


    Serial::putTask((uint8 *)"Memory manager", false);
    mm((multiboot_info_t *)multiboot_info);
    Serial::putTask((uint8 *)"Memory manager", true);


    Serial::putTask((uint8 *)"VESA", false);
    VbeVideoMode vesa;
    vesa.init();
    Serial::putTask((uint8 *)"VESA", true);


    Serial::putTask((uint8 *)"ECS Environement", false);
    Ecos ecos;
    initEcos(&ecos);
    Serial::putTask((uint8 *)"ECS Environement", true);


    Serial::putTask((uint8 *)"ECOS", false);
    ecos.run();
}