#ifndef IVIDEOMODE_HPP_
#define IVIDEOMODE_HPP_

#include <libraries/std/types/CTypes.hpp>
#include <libraries/std/types/Graphic.hpp>

class IVideoMode {
    public:
        virtual bool init() = 0;

        // draw
        virtual void drawPixel(vector2d position, color color) = 0;
        virtual void drawRect(rect rect, color color) = 0;
        virtual void drawCircle(vector2d position, uint32 radius, color color) = 0;

        // display
        virtual void display() = 0;
};

#endif /* !IVIDEOMODE_HPP_ */
