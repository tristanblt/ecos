#ifndef VESAVIDEOMODE_HPP_
#define VESAVIDEOMODE_HPP_

#include <drivers/interfaces/IVideoMode.hpp>
#include <kernel/arch.hpp>
#include <libraries/std/io/IOPort.hpp>
#include <libraries/std/Memory.hpp>

#define VESA_VBE_VENDOR 0x1234
#define VESA_VBE_DEVICE 0x1111

#define VBE_DISPI_IOPORT_INDEX 0x1CE
#define VBE_DISPI_IOPORT_DATA 0x1CF

#define VBE_DISPI_INDEX_ID 0
#define VBE_DISPI_INDEX_XRES 1
#define VBE_DISPI_INDEX_YRES 2
#define VBE_DISPI_INDEX_BPP 3
#define VBE_DISPI_INDEX_ENABLE 4
#define VBE_DISPI_INDEX_BANK 5
#define VBE_DISPI_INDEX_VIRT_WIDTH 6
#define VBE_DISPI_INDEX_VIRT_HEIGHT 7
#define VBE_DISPI_INDEX_X_OFFSET 8
#define VBE_DISPI_INDEX_Y_OFFSET 9

#define VBE_DISPI_DISABLED 0x00
#define VBE_DISPI_ENABLED 0x01
#define VBE_DISPI_LFB_ENABLED 0x40
#define VBE_DISPI_NOCLEARMEM 0x80

#define VBE_WINDOW_WIDTH 1600
#define VBE_WINDOW_HEIGHT 900
#define VBE_WINDOW_DEPTH 32

class VbeVideoMode : public IVideoMode
{
public:
    VbeVideoMode() = default;
    ~VbeVideoMode() = default;

    bool init();

    // draw
    void drawPixel(vector2d position, color color);
    void drawRect(rect rect, color color);
    void drawCircle(vector2d position, uint32 radius, color color);
    void drawHorizontalLine(vector2d position, uint32 size, color color);

    // display
    void display();

private:
    // init
    void initDisplay(uint16 width, uint16 height, uint16 depth);

    // utils
    void vbeWrite(uint16 index, uint16 value);
    void vbeDisable();
    void vbeEnable();
    void vbeAreaGrow(vector2d position);

    uint8 _vbeBus;
    uint8 _vbeDev;
    uint8 _vbeFunction;
    uint8 *_vbeFb;
    uint32 *_vbeFbDouble[2];
    uint8 _vbeFbCurrent;
    uint8 _vbeFbPages;
    uint16 _width;
    uint16 _height;
    uint16 _depth;
    uint32 _scanline;
    uint32 _pixelSize;
    uint8 _fontSizeX;
    uint8 _fontSizeY;
    uint32 _updateX1;
    uint32 _updateX0;
    uint32 _updateY1;
    uint32 _updateY0;

    uint32 *_pixelBuffer;
};

#endif /* !VESAVIDEOMODE_HPP_ */
