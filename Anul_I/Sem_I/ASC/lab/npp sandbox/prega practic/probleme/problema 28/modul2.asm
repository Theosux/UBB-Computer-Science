bits 32

global _modul2

segment data public data use32

segment code public code use32

_modul2:
    push ebp
    mov ebp, esp
    
    push esi
    push edi
    
    mov esi, [ebp + 8]
    mov edi, [ebp + 12]
    
    xor eax, eax
    
    bucla:
        lodsb
        cmp AL, 0
        je gata
        cmp AL, 'A'
        jb sari
        cmp AL, 'Z'
        ja sari
        
        stosb
        
        sari:
            jmp bucla
    gata:
    stosb
    
    pop edi
    pop esi
    
    mov esp, ebp
    pop ebp
    
    ret