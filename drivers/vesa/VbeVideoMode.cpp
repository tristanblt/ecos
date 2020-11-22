#include "VbeVideoMode.hpp"

bool VbeVideoMode::init()
{
    uint32_t aux, *pagetable;

    if (!pci_find(VESA_VBE_VENDOR, VESA_VBE_DEVICE, &_vbe_bus, &_vbe_dev, &_vbe_function))
        return (false);
    _font_xsize = 8;
    _font_ysize = 8;
    aux = pci_read(_vbe_bus, _vbe_dev, _vbe_function, PCI_BAR0);
    _vbe_fb = (uint8_t *)0xD0000000;
    for (uint32_t i = 0; i < 0x1000000; i += 0x1000)
        page_map((uint32_t)((aux & 0xFFFFFFF0) + i), ((uint32_t)_vbe_fb + i));
    _vbe_fb_current = 0;
    _vbe_fb_double[0] = (uint32_t *)_vbe_fb;
    _vbe_fb_double[1] = (uint32_t *)_vbe_fb;
    _update_x0 = _update_y0 = 0xFFFFFFFF;
    _update_x1 = _update_y1 = 0x0;
    init_display(VBE_WINDOW_WIDTH, VBE_WINDOW_HEIGHT, VBE_WINDOW_DEPTH);
    return (true);
}

void VbeVideoMode::vbe_write(uint16_t index, uint16_t value)
{
    outportw(VBE_DISPI_IOPORT_INDEX, index);
    outportw(VBE_DISPI_IOPORT_DATA, value);
}

void VbeVideoMode::vbe_disable()
{
    vbe_write(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_DISABLED);
}

void VbeVideoMode::vbe_enable()
{
    vbe_write(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_ENABLED | VBE_DISPI_LFB_ENABLED);
}

void VbeVideoMode::init_display(uint16_t width, uint16_t height, uint16_t depth)
{
    switch (depth)
    {
    case 32:
        _scanline = width * 4;
        _pixel_size = 4;
        break;
    default:
        return;
    }
    _width = width;
    _height = height;
    _depth = depth;
    _vbe_fb_double[1] = (uint32_t *)(_vbe_fb + _width * _height * (_depth >> 3));
    vbe_disable();
    vbe_write(VBE_DISPI_INDEX_XRES, width);
    vbe_write(VBE_DISPI_INDEX_YRES, height);
    vbe_write(VBE_DISPI_INDEX_BPP, depth);
    vbe_write(VBE_DISPI_INDEX_VIRT_WIDTH, width);
    vbe_write(VBE_DISPI_INDEX_Y_OFFSET, 0);
    vbe_enable();
}

void VbeVideoMode::vbe_area_grow(vector2d_t position)
{
    if (position.x > _update_x1)
        _update_x1 = position.x;
    if (position.x < _update_x0)
        _update_x0 = position.x;
    if (position.y > _update_y1)
        _update_y1 = position.y;
    if (position.y < _update_y0)
        _update_y0 = position.y;
}

void VbeVideoMode::draw_horizontal_line(vector2d_t position, uint32_t size, color_t color)
{
    uint32_t offset;

    if (position.x > _width || position.y > _height)
        return;
    if (position.x + size > _width)
        size = _width - position.x;
    offset = position.y * _width + position.x;
    //_vbe_fb_double[1][0] = color.value;
    memset32(&_vbe_fb_double[1][offset], color.value, size);
}

void VbeVideoMode::draw_pixel(vector2d_t position, color_t color)
{
    uint32_t offset;

    if (position.x > _width || position.y > _height)
        return;
    offset = position.y * _width + position.x;
    _pixel_buffer[offset] = color.value;
}

void VbeVideoMode::draw_rect(rect_t rect, color_t color)
{
    for (uint32_t y = 0; y < rect.h; y++)
        draw_horizontal_line({rect.x, y + rect.y}, rect.w, color);
}

void VbeVideoMode::draw_circle(vector2d_t position, uint32_t radius, color_t color)
{
    int r2 = radius * radius;
    int area = r2 << 2;
    int rr = radius << 1;

    for (int i = 0; i < area; i++) {
        int tx = (i % rr) - radius;
        int ty = (i / rr) - radius;

        if (tx * tx + ty * ty <= r2)
            draw_pixel({position.x + tx, position.y + ty}, color);
    }
}

void VbeVideoMode::display()
{
    memcpy32(_vbe_fb_double[1], _vbe_fb_double[0], _width * _height);
}