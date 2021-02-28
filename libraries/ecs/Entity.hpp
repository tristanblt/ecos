#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <drivers/serial/Serial.hpp>
#include <libraries/std/dynamicList/DynamicList.hpp>
#include <libraries/ecs/interfaces/IComponent.hpp>
#include <libraries/ecs/utils/IDOf.hpp>

namespace ecs {
    class Ecos;
    class Entity {
        public:
            Entity(Ecos *ecos);
            ~Entity() = default;

            template <typename T>
            void addComponent(IComponent *component)
            {
                _components.add(component);
                _ecos->addComponent(IDOf::component<T>(), component);
            }

            void removeComponent();
            void getComponent();

            void getComponentModel();

        private:
            std::DynamicList<IComponent> _components;
            Ecos *_ecos;
    };
}

#endif /* !ENTITY_HPP_ */
