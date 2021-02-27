#include "VbeVideoMode.hpp"

using namespace std;

bool VbeVideoMode::init()
{
    uint32 aux, *pagetable;

    if (!pciFind(VESA_VBE_VENDOR, VESA_VBE_DEVICE, &_vbeBus, &_vbeDev, &_vbeFunction))
        return (false);
    _fontSizeX = 8;
    _fontSizeY = 8;
    aux = pciRead(_vbeBus, _vbeDev, _vbeFunction, PCI_BAR0);
    _vbeFb = (uint8 *)0xD0000000;
    for (uint32 i = 0; i < 0x1000000; i += 0x1000)
        pageMap((uint32)((aux & 0xFFFFFFF0) + i), ((uint32)_vbeFb + i));
    _vbeFbCurrent = 0;
    _vbeFbDouble[0] = (uint32 *)_vbeFb;
    _vbeFbDouble[1] = (uint32 *)_vbeFb;
    _updateX0 = _updateY0 = 0xFFFFFFFF;
    _updateX1 = _updateY1 = 0x0;
    initDisplay(VBE_WINDOW_WIDTH, VBE_WINDOW_HEIGHT, VBE_WINDOW_DEPTH);
    return (true);
}

void VbeVideoMode::vbeWrite(uint16 index, uint16 value)
{
    IOPort::outPortW(VBE_DISPI_IOPORT_INDEX, index);
    IOPort::outPortW(VBE_DISPI_IOPORT_DATA, value);
}

void VbeVideoMode::vbeDisable()
{
    vbeWrite(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_DISABLED);
}

void VbeVideoMode::vbeEnable()
{
    vbeWrite(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_ENABLED | VBE_DISPI_LFB_ENABLED);
}

void VbeVideoMode::initDisplay(uint16 width, uint16 height, uint16 depth)
{
    switch (depth)
    {
    case 32:
        _scanline = width * 4;
        _pixelSize = 4;
        break;
    default:
        return;
    }
    _width = width;
    _height = height;
    _depth = depth;
    _vbeFbDouble[1] = (uint32 *)(_vbeFb + _width * _height * (_depth >> 3));
    vbeDisable();
    vbeWrite(VBE_DISPI_INDEX_XRES, width);
    vbeWrite(VBE_DISPI_INDEX_YRES, height);
    vbeWrite(VBE_DISPI_INDEX_BPP, depth);
    vbeWrite(VBE_DISPI_INDEX_VIRT_WIDTH, width);
    vbeWrite(VBE_DISPI_INDEX_Y_OFFSET, 0);
    vbeEnable();
}

void VbeVideoMode::vbeAreaGrow(vector2d position)
{
    if (position.x > _updateX1)
        _updateX1 = position.x;
    if (position.x < _updateX0)
        _updateX0 = position.x;
    if (position.y > _updateY1)
        _updateY1 = position.y;
    if (position.y < _updateY0)
        _updateY0 = position.y;
}

void VbeVideoMode::drawHorizontalLine(vector2d position, uint32 size, color color)
{
    uint32 offset;

    if (position.x > _width || position.y > _height)
        return;
    if (position.x + size > _width)
        size = _width - position.x;
    offset = position.y * _width + position.x;
    //_vbe_fb_double[1][0] = color.value;
    Memory::set32(&_vbeFbDouble[1][offset], color.value, size);
}

void VbeVideoMode::drawPixel(vector2d position, color color)
{
    uint32 offset;

    if (position.x > _width || position.y > _height)
        return;
    offset = position.y * _width + position.x;
    _pixelBuffer[offset] = color.value;
}

void VbeVideoMode::drawRect(rect rect, color color)
{
    for (uint32 y = 0; y < rect.h; y++)
        drawHorizontalLine({rect.x, y + rect.y}, rect.w, color);
}

void VbeVideoMode::drawCircle(vector2d position, uint32 radius, color color)
{
    uint32 r2 = radius * radius;
    uint32 area = r2 << 2;
    uint32 rr = radius << 1;

    for (uint32 i = 0; i < area; i++) {
        uint32 tx = (i % rr) - radius;
        uint32 ty = (i / rr) - radius;

        if (tx * tx + ty * ty <= r2)
            drawPixel({position.x + tx, position.y + ty}, color);
    }
}

void VbeVideoMode::display()
{
    Memory::cpy32(_vbeFbDouble[1], _vbeFbDouble[0], _width * _height);
}