OUTPUT_FORMAT(elf32-i386)
ENTRY(start)

PADDR_BASE = 0x100000;
VADDR_BASE = 0xC0000000;

SECTIONS
{
   . = VADDR_BASE;
   kernel_vaddr_start = .;
   _kernel_vaddr_start = .;
   kernel_paddr_start = PADDR_BASE; _kernel_paddr_start = PADDR_BASE;

   .multiboot ALIGN (0x1000) : AT(PADDR_BASE)
   {
       *(.multiboot)
   }

   .text ALIGN (0x1000) :
   {
       *(.text)
   }

   .rodata ALIGN (0x1000):
   {
       *(.rodata*)
   }

   .data ALIGN (0x1000) :
   {
       *(.data)
   }

   .bss ALIGN (0x1000) :
   {
       *(.bss)
       *(COMMON)
       kernel_paddr_end = .; _kernel_paddr_end = .;
   }
   kernel_vaddr_end = .;
   _kernel_vaddr_end = .;
 }
