#ifndef WINDOWSYSTEM_HPP_
#define WINDOWSYSTEM_HPP_

#include <libraries/ecs/interfaces/ISystem.hpp>
#include <drivers/serial/Serial.hpp>

namespace systems {
    class WindowSystem : public ecs::ISystem {
        public:
            WindowSystem() = default;
            ~WindowSystem() = default;

            void start();
            void update();
            void stop();

        private:
    };
}

#endif /* !WINDOWSYSTEM_HPP_ */
