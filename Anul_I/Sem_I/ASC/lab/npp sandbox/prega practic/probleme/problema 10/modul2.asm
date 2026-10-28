bits 32

global _modul2

extern _printf

segment data public data use32
    format1 db "Primul sir apare ca subsecventa in restul", 0
    format2 db "Primul sir NU apare ca subsecventa in restul", 0
segment code public code use32
    _modul2:
    
    ;cod intrare
    push ebp
    mov ebp, esp
    
    mov eax, [ebp+8]
    
    cmp eax, 1
    je apare
    ; altfel, nu apare:
        push dword format2
        call _printf
        add esp, 4
    jmp sari
    apare:
        push dword format1
        call _printf
        add esp, 4
    sari:
    ;cod iesire
    mov esp, ebp
    pop ebp
    ret
    