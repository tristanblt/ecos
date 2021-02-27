#include "Ecos.hpp"

using namespace ecs;

void Ecos::start()
{
    // _systems[0]->start();
}

void Ecos::run()
{
    start();
    // while (true) {

    // }
    stop();
}

void Ecos::stop()
{

}

Entity *Ecos::addEntity()
{
    return(_entities.add());
}

void Ecos::removeEntity()
{

}

void Ecos::addSystem(ISystem *system)
{
    _systems.add(system);
}