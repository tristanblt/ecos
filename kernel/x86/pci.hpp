#ifndef _PCI_H_
#define _PCI_H_

#include <libraries/std/types/CTypes.hpp>

#define PCI_VENDOR_DEVICE 0x00
#define PCI_CLASS_SUBCLASS 0x08
#define PCI_BAR0 0x10
#define PCI_BAR1 PCI_BAR0 + 4
#define PCI_BAR2 PCI_BAR1 + 4
#define PCI_BAR3 PCI_BAR2 + 4
#define PCI_BAR4 PCI_BAR3 + 4
#define PCI_BAR5 PCI_BAR4 + 4

uint8 pciFind(uint32 vendor, uint32 device, uint8 *bus, uint8 *dev, uint8 *function);
uint32 pciRead(uint32 bus, uint32 device, uint32 function, uint32 offset);
void pciWrite(uint32 bus, uint32 device, uint32 function, uint32 offset, uint32 data);

#endif
