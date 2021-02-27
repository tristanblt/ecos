#ifndef ECOS_HPP_
#define ECOS_HPP_

#include <libraries/ecs/Entity.hpp>
#include <libraries/ecs/interfaces/ISystem.hpp>
#include <drivers/serial/Serial.hpp>

namespace ecs {
    class Ecos {
        public:
            Ecos() = default;
            ~Ecos() = default;

            void run();

            Entity *addEntity();
            void removeEntity();

            void addSystem(ISystem *system);

        private:
            void start();
            void stop();

            std::DynamicList<Entity> _entities;
            std::DynamicList<ISystem> _systems;
    };
}

#endif /* !ECOS_HPP_ */
