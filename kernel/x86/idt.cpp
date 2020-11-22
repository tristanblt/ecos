
#include "arch.hpp"
#include "pic.hpp"

extern "C" void load_idt();

isr_call_vector_t isr_call_vector;
isr_call_vector_t *isr_call_ptr_vector = 0;

struct fault_name
{
    char *name;
    uint8_t has_errcode;
};

struct fault_name fault_names[] = {
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

extern "C" uint32_t isr_fault(int_regs_t *regs)
{
}

uint32_t page_fault_handler(int_regs_t *regs)
{
    while (1)
        __asm__ __volatile__("cli\n");
}

uint32_t irq7_handler(int_regs_t *regs)
{
}

void isr_install()
{
    ISR_SET_HANDLER(14, page_fault_handler);
    IRQ_SET_HANDLER(7, irq7_handler);
}

void idt()
{
    pic();
    load_idt();
    isr_call_ptr_vector = &isr_call_vector;
    isr_install();
}
