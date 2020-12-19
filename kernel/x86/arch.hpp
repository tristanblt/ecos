#ifndef _ARCH_X86_H_
#define _ARCH_X86_H_

#include <libraries/std/types/CTypes.hpp>
#include <kernel/panic.hpp>
#include "page.hpp"
#include "pic.hpp"
#include "pci.hpp"

#define KERNEL_CODE 0x08
#define KERNEL_DATA 0x10
#define USER_CODE 0x18
#define USER_DATA 0x20

extern uint32 kernelStackAddr;

#pragma pack(1)
struct intRegs
{
    uint32 edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32 gs, fs, es, ds;
    uint32 intn, errCode;
    uint32 eip, cs, eflags, useresp, ss;
};

struct kregs
{
    uint32 ebx, esi, edi, ebp; // callee-save
    uint32 eip, eflags;        // CALL/IRET
};

typedef uint32 (*isrCall)(intRegs *);
typedef isrCall isrCallVector[256];

#pragma pack(1)
struct isrVector
{
    unsigned gate;
    isrCall isr_call;
};

struct gdt
{
    uint16 size;
    uint32 offset;
} __attribute__((__packed__));

struct idt
{
    uint16 size;
    uint32 offset;
} __attribute__((__packed__));

struct gdtEntry
{
    uint32 low;
    uint32 high;
} __attribute__((aligned(8)));

struct __attribute__((aligned(8), __packed__)) idtEntry
{
    uint16 offset1; // offset bits 0..15
    uint16 selector; // a code segment selector in GDT or LDT
    uint8 ist;       // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
    uint8 typeAttr; // type and attributes
    uint16 offset2; // offset bits 16..31
};

struct __attribute__((__packed__)) tssEntryStruct
{
    uint32 prevTss;
    uint32 esp0;
    uint32 ss0;
    uint32 esp1;
    uint32 ss1;
    uint32 esp2;
    uint32 ss2;
    uint32 cr3;
    uint32 eip;
    uint32 eflags;
    uint32 eax;
    uint32 ecx;
    uint32 edx;
    uint32 ebx;
    uint32 esp;
    uint32 ebp;
    uint32 esi;
    uint32 edi;
    uint32 es;
    uint32 cs;
    uint32 ss;
    uint32 ds;
    uint32 fs;
    uint32 gs;
    uint32 ldt;
    uint16 trap;
    uint16 iomapBase;
};

extern tssEntryStruct kernelTss;

void syscallSetup();

void isrInstall(void);
void isrInit(void);

extern "C" void isrSetHandler(int num, isrVector *isrVector);
extern "C" void isrGetHandler(int num, isrVector *isrVector);

#define IRQ_SET_HANDLER(irq, handler)     \
    {                                     \
        ASSERT_PANIC(irq <= 0xF);         \
        isrVector v = {0x8E, handler};    \
        isrSetHandler(0x20 + irq, &v);    \
    }
#define ISR_SET_HANDLER(n, handler)       \
    {                                     \
        isrVector v = {0x8E, handler};    \
        isrSetHandler(n, &v);             \
    }

#define arch()         \
    {                  \
        gdt();         \
        idt();         \
        isrInstall();  \
    }

#endif
