#ifndef ECOS_HPP_
#define ECOS_HPP_

#include <libraries/ecs/Entity.hpp>
#include <libraries/ecs/interfaces/ISystem.hpp>
#include <drivers/serial/Serial.hpp>
#include <libraries/std/dynamicMap/DynamicMap.hpp>

namespace ecs {
    class Ecos {
        public:
            Ecos() = default;
            ~Ecos() = default;

            void run();

            Entity *addEntity();
            void removeEntity();

            void addComponent(int componentId, IComponent *component);

            void addSystem(ISystem *system);

            template <typename T>
            std::DynamicList<T> getComponents()
            {
                std::DynamicList<IComponent> oldList = _components.getAll(IDOf::component<T>());
                std::DynamicList<T> newList;

                for (uint32 i = 0; i < oldList.size(); i++)
                    newList.add(static_cast<T *>(oldList[i]));
                return (newList);
            }

        private:
            void start();
            void stop();

            std::DynamicList<Entity> _entities;
            std::DynamicList<ISystem> _systems;
            std::DynamicMap<int, IComponent> _components;
    };
}

#endif /* !ECOS_HPP_ */
