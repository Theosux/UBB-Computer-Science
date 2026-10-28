bits 32

global _modul1

segment data public data use32

segment code public code use32

_modul1:
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
        cmp AL, 'a'
        jb sari
        cmp AL, 'z'
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