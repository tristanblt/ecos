#include "WindowSystem.hpp"

using namespace systems;
using namespace components;

WindowSystem::WindowSystem(VbeVideoMode *vesa) :
    _vesa(vesa)
{

}

void WindowSystem::start()
{

}

void WindowSystem::update()
{
    std::DynamicList<WindowComponent> windows = _ecos->getComponents<WindowComponent>();

    for (int i = 0; i < windows.size(); i++) {
        _vesa->drawRect((rect){i * 400, 0, 200, 200}, (color){0xFF0000});
    }
    _vesa->display();
}

void WindowSystem::stop()
{

}