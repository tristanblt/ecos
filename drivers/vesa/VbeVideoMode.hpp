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
    void draw_pixel(vector2d_t position, color_t color);
    void draw_rect(rect_t rect, color_t color);
    void draw_circle(vector2d_t position, uint32_t radius, color_t color);
    void draw_horizontal_line(vector2d_t position, uint32_t size, color_t color);

    // display
    void display();

private:
    // init
    void init_display(uint16_t width, uint16_t height, uint16_t depth);

    // utils
    void vbe_write(uint16_t index, uint16_t value);
    void vbe_disable();
    void vbe_enable();
    void vbe_area_grow(vector2d_t position);

    uint8_t _vbe_bus;
    uint8_t _vbe_dev;
    uint8_t _vbe_function;
    uint8_t *_vbe_fb;
    uint32_t *_vbe_fb_double[2];
    uint8_t _vbe_fb_current;
    uint8_t _vbe_fb_pages;
    uint16_t _width;
    uint16_t _height;
    uint16_t _depth;
    uint32_t _scanline;
    uint32_t _pixel_size;
    uint8_t _font_xsize;
    uint8_t _font_ysize;
    uint32_t _update_x1;
    uint32_t _update_x0;
    uint32_t _update_y1;
    uint32_t _update_y0;

    uint32_t *_pixel_buffer;
};

#endif /* !VESAVIDEOMODE_HPP_ */
