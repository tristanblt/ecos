global loadGdt
global loadIdt
global loadTss

loadGdt:
    mov   eax, [esp + 4]
    lgdt  [eax]

    jmp 0x08:reload_segment
 reload_segment:
    mov  ax, 0x10
    mov  ds, ax
    mov  es, ax
    mov  fs, ax
    mov  gs, ax
    mov  ss, ax
    ret

loadTss:
    mov   ax, 0x2B
    ltr   ax
    ret
