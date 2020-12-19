#ifndef ENTITY_HPP_
#define ENTITY_HPP_

#include <drivers/serial/Serial.hpp>

namespace ecs {
    class Entity {
        public:
            Entity() = default;
            ~Entity() = default;

            void addComponent();
            void removeComponent();
            void getComponent();

            void getComponentModel();

        protected:
        private:
    };
}

#endif /* !ENTITY_HPP_ */
