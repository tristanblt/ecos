
#include "arch.hpp"
#include "pic.hpp"

extern "C" void loadIdt();

isrCallVector_t isrCallVector;
isrCallVector_t *isrCallPtrVector = 0;

struct faultName
{
    char *name;
    uint8_t hasErrcode;
};

struct faultName faultNames[] = {
    {"Divide-by-Zero", false},
    {"Debug", false},
    {"Non-maskable Interrupt", false},
    {"Breakpoint", false},
    {"Overflow", false},
    {"Bound Range Exceeded", false},
    {"Invalid Opcode", false},
    {"Device Not Available", false},
    {"Double Fault", true},
    {"Coprocessor Segment Overrun", false},
    {"Invalid TSS", true},
    {"Segment Not Present", true},
    {"Stack-Segment Fault", true},
    {"General Protection Fault", true},
    {"Page Fault", true},
    {nullptr, false},
    {"x87 Floating-Point Exception", false},
    {"Alignment Check", true},
    {"Machine Check", false},
    {"SIMD Floating-Point Exception", false},
    {"Virtualization Exception", false},
    {nullptr, false},
    {nullptr, false},
    {nullptr, false},
    {nullptr, false},
    {nullptr, false},
    {nullptr, false},
    {nullptr, false},
    {nullptr, false},
    {nullptr, false},
    {"Security Exception", true},
    {nullptr, false}};

extern "C" uint32_t isrFault(intRegs_t *regs)
{
}

uint32_t pageFaultHandler(intRegs_t *regs)
{
    while (1)
        __asm__ __volatile__("cli\n");
}

uint32_t irq7Handler(intRegs_t *regs)
{
}

void isrInstall()
{
    ISR_SET_HANDLER(14, pageFaultHandler);
    IRQ_SET_HANDLER(7, irq7Handler);
}

void idt()
{
    pic();
    loadIdt();
    isrCallPtrVector = &isrCallVector;
    isrInstall();
}
