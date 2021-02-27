#include <libraries/ecs/Entity.hpp>

using namespace ecs;

void Entity::addComponent(IComponent *component)
{
    _components.add(component);
}