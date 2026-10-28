bits 32

global _afiseaza_total
extern _printf

segment data public data use32
format db "Suma totala este: %d", 0

segment code public code use32
    _afiseaza_total:
    ;cod de intrare
    push ebp
    mov ebp, esp
    ;
    
    mov eax, [ebp + 8]              ; luam suma
    
    push eax
    push dword format
    call _printf                    ; o afisam
    add esp, 4*2
    
    
    ;cod de iesire
    mov esp, ebp
    pop ebp
    ret