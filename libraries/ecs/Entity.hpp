#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <drivers/serial/Serial.hpp>
#include <libraries/std/dynamicList/DynamicList.hpp>
#include <libraries/ecs/interfaces/IComponent.hpp>

namespace ecs {
    class Entity {
        public:
            Entity() = default;
            ~Entity() = default;

            void addComponent();
            void removeComponent();
            void getComponent();

            void getComponentModel();

        private:
            std::DynamicList<IComponent> _components;
    };
}

#endif /* !ENTITY_HPP_ */
