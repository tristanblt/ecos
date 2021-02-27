#include "Ecos.hpp"

using namespace ecs;

void Ecos::start()
{
    for (uint32 i = 0; i < _systems.size(); i++)
        _systems[i]->start();
}

void Ecos::run()
{
    start();
    while (true) {
        for (uint32 i = 0; i < _systems.size(); i++)
            _systems[i]->update();
    }
    stop();
}

void Ecos::stop()
{
    for (uint32 i = 0; i < _systems.size(); i++)
        _systems[i]->stop();
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