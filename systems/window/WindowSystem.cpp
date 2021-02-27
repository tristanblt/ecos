#include "WindowSystem.hpp"

using namespace systems;

WindowSystem::WindowSystem(VbeVideoMode *vesa) :
    _vesa(vesa)
{

}

void WindowSystem::start()
{

}

void WindowSystem::update()
{
    _vesa->drawRect((rect){0, 0, 200, 200}, (color){0xFF0000});
    _vesa->display();
}

void WindowSystem::stop()
{

}