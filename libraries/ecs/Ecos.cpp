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
    return(_entities.add(new Entity(this)));
}

void Ecos::removeEntity()
{

}

void Ecos::addComponent(int componentId, IComponent *component)
{
    _components.add(componentId, component);
}

void Ecos::addSystem(ISystem *system)
{
    system->setEcos(this);
    _systems.add(system);
}