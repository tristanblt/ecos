#ifndef VESAVIDEOMODE_HPP_
#define VESAVIDEOMODE_HPP_

#include <drivers/interfaces/IVideoMode.hpp>
#include <kernel/arch.hpp>
#include <libraries/std/io/ioport.hpp>

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

void *memset32(void *dest, uint32_t val, uint32_t len);
void *memset8(void *dest, uint8_t val, uint32_t len);
void *malloc(uint32_t size);
void memcpy32(void *src, void *dst, uint32_t size);

class VbeVideoMode : public IVideoMode
{
public:
    VbeVideoMode() = default;
    ~VbeVideoMode() = default;

    bool init();

    // draw
    void drawPixel(vector2d_t position, color_t color);
    void drawRect(rect_t rect, color_t color);
    void drawCircle(vector2d_t position, uint32_t radius, color_t color);
    void drawHorizontalLine(vector2d_t position, uint32_t size, color_t color);

    // display
    void display();

private:
    // init
    void initDisplay(uint16_t width, uint16_t height, uint16_t depth);

    // utils
    void vbeWrite(uint16_t index, uint16_t value);
    void vbeDisable();
    void vbeEnable();
    void vbeAreaGrow(vector2d_t position);

    uint8_t _vbeBus;
    uint8_t _vbeDev;
    uint8_t _vbeFunction;
    uint8_t *_vbeFb;
    uint32_t *_vbeFbDouble[2];
    uint8_t _vbeFbCurrent;
    uint8_t _vbeFbPages;
    uint16_t _width;
    uint16_t _height;
    uint16_t _depth;
    uint32_t _scanline;
    uint32_t _pixelSize;
    uint8_t _fontSizeX;
    uint8_t _fontSizeY;
    uint32_t _updateX1;
    uint32_t _updateX0;
    uint32_t _updateY1;
    uint32_t _updateY0;

    uint32_t *_pixelBuffer;
};

#endif /* !VESAVIDEOMODE_HPP_ */
