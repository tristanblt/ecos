#include <libraries/std/types/CTypes.hpp>
#include <libraries/std/io/ioport.hpp>
#include <kernel/arch.hpp>

#define PCI_CONFIG 0xCF8
#define PCI_DATA 0xCFC

uint32 pciRead(uint32 bus, uint32 device, uint32 function, uint32 offset)
{
    uint32 reg = 0x80000000;

    reg |= (bus & 0xFF) << 16;
    reg |= (device & 0x1F) << 11;
    reg |= (function & 0x7) << 8;
    reg |= (offset & 0xFF) & 0xFC;
    outPortL(PCI_CONFIG, reg);
    return inPortL(PCI_DATA);
}

void pciWrite(uint32 bus, uint32 device, uint32 function, uint32 offset, uint32 data)
{
    uint32 reg = 0x80000000;

    reg |= (bus & 0xFF) << 16;
    reg |= (device & 0x1F) << 11;
    reg |= (function & 0x7) << 8;
    reg |= offset & 0xFC;
    outPortL(PCI_CONFIG, reg);
    outPortL(PCI_DATA, data);
}

uint8 pciFind(uint32 vendor, uint32 device, uint8 *bus, uint8 *dev, uint8 *function)
{
    uint32 vendDev, b, d, f, myVendDev;

    myVendDev = (vendor & 0xFFFF) | (device << 16);
    for (b = 0; b < 256; b++)
        for (d = 0; d < 32; d++)
            for (f = 0; f < 8; f++) {
                vendDev = pciRead(b, d, f, PCI_VENDOR_DEVICE);
                if (vendDev == myVendDev) {
                    *bus = b;
                    *dev = d;
                    *function = f;
                    return (true);
                }
            }
    return (false);
}

uint8 pciFind_class2(int8 class2, uint8 subclass2, uint8 *bus, uint8 *dev, uint8 *function)
{
    uint32 b, d, f;
    uint16 myClsSub, clsSub;

    myClsSub = class2 | (subclass2 << 8);
    for (b = 0; b < 256; b++)
        for (d = 0; d < 32; d++)
            for (f = 0; f < 8; f++) {
                clsSub = pciRead(b, d, f, PCI_CLASS_SUBCLASS) >> 16;
                if (clsSub == myClsSub) {
                    *bus = b;
                    *dev = d;
                    *function = f;
                    return (true);
                }
            }
    return (false);
}

void pciest()
{
    uint32 vendDev, b, d, f;
    for (b = 0; b < 256; b++)
        for (d = 0; d < 32; d++)
            for (f = 0; f < 8; f++)
                vendDev = pciRead(b, d, f, PCI_VENDOR_DEVICE);
}
