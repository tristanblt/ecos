#ifndef WINDOWSYSTEM_HPP_
#define WINDOWSYSTEM_HPP_

#include <libraries/ecs/ASystem.hpp>
#include <libraries/ecs/Ecos.hpp>
#include <drivers/serial/Serial.hpp>
#include <drivers/vesa/VbeVideoMode.hpp>

#include <components/window/WindowComponent.hpp>
namespace systems {
    class WindowSystem : public ecs::ASystem {
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
