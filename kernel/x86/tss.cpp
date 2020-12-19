#include "arch.hpp"

tssEntry_t kernelTss;

void tss()
{
    kernelTss.ss0 = KERNEL_DATA;
    __asm__ __volatile__("movl %%esp, %0;":"=m"(kernelTss.esp0)::"%eax");
    __asm__ __volatile__("movl %%cr3, %%eax; movl %%eax, %0;":"=m"(kernelTss.cr3)::"%eax");
    kernelTss.cs = KERNEL_CODE;
    kernelTss.ss = kernelTss.ds = kernelTss.es = kernelTss.fs = kernelTss.gs = KERNEL_DATA;
    kernelTss.iomapBase = 104;
}

void tssSetEsp0(uint32_t esp0)
{
    kernelTss.esp0 = esp0;
}
