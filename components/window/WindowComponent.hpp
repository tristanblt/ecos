#ifndef TEST_HPP_
#define TEST_HPP_

#include <libraries/ecs/interfaces/IComponent.hpp>

namespace components {
class WindowComponent : public ecs::IComponent {
    public:
        WindowComponent() = default;
        ~WindowComponent() = default;

    private:
};
}

#endif /* !TEST_HPP_ */
