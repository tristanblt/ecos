#ifndef TEST_HPP_
#define TEST_HPP_

#include <libraries/ecs/interfaces/IComponent.hpp>

namespace components {
class Window : public ecs::IComponent {
    public:
        Window() = default;
        ~Window() = default;

    private:
};
}

#endif /* !TEST_HPP_ */
