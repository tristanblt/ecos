#ifndef WINDOWSYSTEM_HPP_
#define WINDOWSYSTEM_HPP_

#include <libraries/ecs/interfaces/ISystem.hpp>
#include <drivers/serial/Serial.hpp>
#include <drivers/vesa/VbeVideoMode.hpp>

namespace systems {
    class WindowSystem : public ecs::ISystem {
        public:
            WindowSystem(VbeVideoMode *vesa);
            ~WindowSystem() = default;

            void start();
            void update();
            void stop();

        private:
            VbeVideoMode *_vesa;
    };
}

#endif /* !WINDOWSYSTEM_HPP_ */
