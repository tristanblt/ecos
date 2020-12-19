#ifndef _ARCH_X86_H_
#define _ARCH_X86_H_

#include <libraries/std/types.hpp>
#include <kernel/panic.hpp>
#include "page.hpp"
#include "pic.hpp"
#include "pci.hpp"

#define KERNEL_CODE 0x08
#define KERNEL_DATA 0x10
#define USER_CODE 0x18
#define USER_DATA 0x20

extern uint32_t kernelStackAddr;

#pragma pack(1)
typedef struct
{
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t gs, fs, es, ds;
    uint32_t intn, errCode;
    uint32_t eip, cs, eflags, useresp, ss;
} intRegs_t;

typedef struct
{
    uint32_t ebx, esi, edi, ebp; // callee-save
    uint32_t eip, eflags;        // CALL/IRET
} kregs_t;

typedef uint32_t (*isrCall_t)(intRegs_t *);
typedef isrCall_t isrCallVector_t[256];

#pragma pack(1)
typedef struct
{
    unsigned gate;
    isrCall_t isr_call;
} isrVector_t;

struct gdt
{
    uint16_t size;
    uint32_t offset;
} __attribute__((__packed__));

struct idt
{
    uint16_t size;
    uint32_t offset;
} __attribute__((__packed__));

struct gdtEntry
{
    uint32_t low;
    uint32_t high;
} __attribute__((aligned(8)));

typedef struct idtEntry
{
    uint16_t offset1; // offset bits 0..15
    uint16_t selector; // a code segment selector in GDT or LDT
    uint8_t ist;       // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
    uint8_t typeAttr; // type and attributes
    uint16_t offset2; // offset bits 16..31
} __attribute__((aligned(8), __packed__)) idtEntry_t;

struct tssEntryStruct
{
    uint32_t prevTss;
    uint32_t esp0;
    uint32_t ss0;
    uint32_t esp1;
    uint32_t ss1;
    uint32_t esp2;
    uint32_t ss2;
    uint32_t cr3;
    uint32_t eip;
    uint32_t eflags;
    uint32_t eax;
    uint32_t ecx;
    uint32_t edx;
    uint32_t ebx;
    uint32_t esp;
    uint32_t ebp;
    uint32_t esi;
    uint32_t edi;
    uint32_t es;
    uint32_t cs;
    uint32_t ss;
    uint32_t ds;
    uint32_t fs;
    uint32_t gs;
    uint32_t ldt;
    uint16_t trap;
    uint16_t iomapBase;
} __attribute__((__packed__));

typedef struct tssEntryStruct tss_t;
typedef struct tssEntryStruct tssEntry_t;

extern tssEntry_t kernelTss;

void syscallSetup();

void isrInstall(void);
void isrInit(void);

extern "C" void isrSetHandler(int num, isrVector_t *isrVector);
extern "C" void isrGetHandler(int num, isrVector_t *isrVector);

#define IRQ_SET_HANDLER(irq, handler)     \
    {                                     \
        ASSERT_PANIC(irq <= 0xF);         \
        isrVector_t v = {0x8E, handler}; \
        isrSetHandler(0x20 + irq, &v);  \
    }
#define ISR_SET_HANDLER(n, handler)       \
    {                                     \
        isrVector_t v = {0x8E, handler}; \
        isrSetHandler(n, &v);           \
    }

#define arch()         \
    {                  \
        gdt();         \
        idt();         \
        isrInstall(); \
    }

#endif
