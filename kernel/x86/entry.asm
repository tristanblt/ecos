bits 32

global start
extern kernel_stack_addr
global pageDirectory
extern kmain

%define kernel_virt2phys -0xBFF00000


section .multiboot
        MBOOT_HEADER_MAGIC  equ 0x1BADB002
        MBOOT_PAGE_ALIGN    equ 1 << 0
        MBOOT_MEM_INFO      equ 1 << 1
        MBOOT_GRAPH_MODE    equ 1 << 2
        MBOOT_HEADER_FLAGS  equ MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO | MBOOT_GRAPH_MODE
        MBOOT_CHECKSUM      equ -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

        dd MBOOT_HEADER_MAGIC
        dd MBOOT_HEADER_FLAGS
        dd MBOOT_CHECKSUM

        dd 0
        dd 0
        dd 0
        dd 0
        dd 0

        dd 0
        dd 640
        dd 480
        dd 32

section .text

start:
    cli

    mov     edx, ebx
    mov     esp, kernel_stack

    mov     eax, 0x0
    mov     ebx, 0x0
    .fill_table0:
         mov    ecx, ebx
         or     ecx, 3
         mov    [page_table0+kernel_virt2phys+eax*4], ecx
         add    ebx, 4096
         inc    eax
         cmp    eax, 1024
         je     .end0
         jmp    .fill_table0
    .end0:

    mov     eax, 0x0
    mov     ebx, 0x100000
    .fill_table:
         mov    ecx, ebx
         or     ecx, 3
         mov    [page_table768+kernel_virt2phys+eax*4], ecx
         add    ebx, 4096
         inc    eax
         cmp    eax, 1024
         je     .end
         jmp    .fill_table
    .end:

    mov     eax, page_table0
    add     eax, kernel_virt2phys
    and     eax, 0xFFFFF000
    or      eax, 3
    mov     ebx, pageDirectory
    add     ebx, kernel_virt2phys
    mov     [ebx], eax

    mov     eax, page_table768
    add     eax, kernel_virt2phys
    and     eax, 0xFFFFF000
    or      eax, 3
    mov     ebx, pageDirectory
    add     ebx, kernel_virt2phys
    mov     [ebx+768*4], eax

    mov     eax, pageDirectory
    and     eax, 0xFFFFF000
    add     eax, kernel_virt2phys

    mov     cr3, eax
    mov     eax, cr0
    or      eax, 0x80000001

    mov     cr0, eax

    lea     ebx, [go_to_virtual]
    jmp     ebx

go_to_virtual:
    push    edx
    call    kmain

    hlt
    jmp $

section .data

section .bss
align 0x1000

pageDirectory:
    resb  0x1000
page_table0:
    resb  0x1000
page_table768:
    resb  0x1000

kernel_stack_end:
    resb    8192
kernel_stack:
