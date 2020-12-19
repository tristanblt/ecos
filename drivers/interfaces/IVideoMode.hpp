#ifndef IVIDEOMODE_HPP_
#define IVIDEOMODE_HPP_

#include <libraries/std/types.hpp>
#include <libraries/std/video.hpp>

class IVideoMode {
    public:
        virtual bool init() = 0;

        // draw
        virtual void drawPixel(vector2d_t position, color_t color) = 0;
        virtual void drawRect(rect_t rect, color_t color) = 0;
        virtual void drawCircle(vector2d_t position, uint32_t radius, color_t color) = 0;

        // display
        virtual void display() = 0;
};

#endif /* !IVIDEOMODE_HPP_ */
