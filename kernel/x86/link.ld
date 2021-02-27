OUTPUT_FORMAT(elf32-i386)
ENTRY(start)

PADDR_BASE = 0x100000;
VADDR_BASE = 0xC0000000;

SECTIONS
{
   . = VADDR_BASE;
   kernelVaddrStart = .;
   kernelPaddrStart = PADDR_BASE; _kernelPaddrStart = PADDR_BASE;

   .multiboot ALIGN (0x1000) : AT(PADDR_BASE)
   {
       *(.multiboot)
   }

   .text ALIGN (0x1000) :
   {
       *(.text*)
       *(.rodata*)
       *(.gnu.linkonce.t.*)
   }

   .data ALIGN (0x1000) :
   {
       *(.data*)

       *(.gnu.linkonce.d.*)
   }

   .bss ALIGN (0x1000) :
   {
       *(.bss*)
       *(COMMON)
       *(.gnu.linkonce.b.*)
       kernelPaddrEnd = .; _kernelPaddrEnd = .;
   }

   kernelVaddrEnd = .;

   /DISCARD/ :
   {
        *(.comment)
   }
 }
