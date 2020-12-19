#include <libraries/std/types.hpp>
#include <libraries/std/io/ioport.hpp>
#include <kernel/arch.hpp>

#define PCI_CONFIG 0xCF8
#define PCI_DATA 0xCFC

uint32_t pciRead(uint32_t bus, uint32_t device, uint32_t function, uint32_t offset)
{
    uint32_t reg = 0x80000000;

    reg |= (bus & 0xFF) << 16;
    reg |= (device & 0x1F) << 11;
    reg |= (function & 0x7) << 8;
    reg |= (offset & 0xFF) & 0xFC;
    outPortL(PCI_CONFIG, reg);
    return inPortL(PCI_DATA);
}

void pciWrite(uint32_t bus, uint32_t device, uint32_t function, uint32_t offset, uint32_t data)
{
    uint32_t reg = 0x80000000;

    reg |= (bus & 0xFF) << 16;
    reg |= (device & 0x1F) << 11;
    reg |= (function & 0x7) << 8;
    reg |= offset & 0xFC;
    outPortL(PCI_CONFIG, reg);
    outPortL(PCI_DATA, data);
}

uint8_t pciFind(uint32_t vendor, uint32_t device, uint8_t *bus, uint8_t *dev, uint8_t *function)
{
    uint32_t vendDev, b, d, f, myVendDev;

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

uint8_t pciFind_class2(int8_t class2, uint8_t subclass2, uint8_t *bus, uint8_t *dev, uint8_t *function)
{
    uint32_t b, d, f;
    uint16_t myClsSub, clsSub;

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

void pci_test()
{
    uint32_t vendDev, b, d, f;
    for (b = 0; b < 256; b++)
        for (d = 0; d < 32; d++)
            for (f = 0; f < 8; f++)
                vendDev = pciRead(b, d, f, PCI_VENDOR_DEVICE);
}
