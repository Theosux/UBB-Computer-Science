bits 32

global _modul1

segment data public data use32

segment code public code use32
    _modul1:
    ;cod intrare
    push ebp
    mov ebp, esp
    push ebx
    push esi
    push edi
    
    mov esi, [ebp + 8]
    mov edi, [ebp +12]
    
    xor ecx, ecx            ; contor nr cifre
    cld
    parcurgere:
        lodsb
        
        cmp AL, 0
        je iesi
        
        inc ecx
        jmp parcurgere
    iesi:

    mov esi, [ebp + 8]    
    
    test ecx, 1
    jnz impar
    
    ; aici avem cazul cu numar par de cifre
    add edi, ecx
    mov ebx, ecx
    dec edi
    lodsb
    std
    stosb
    cld
    dec ecx
    mov edi, [ebp +12]
    bucla:
        lodsb
        stosb
    loop bucla
    mov edi, [ebp+12]
    add edi, ebx
    mov byte [edi], 0
    
    jmp final
    
    impar:
    cld
    bucla2:
       lodsb
       stosb
    loop bucla2
    mov byte [edi], 0
    
    final:
    
    ;cod iesire
    pop edi
    pop esi
    pop ebx
    mov esp, ebp
    pop ebp
    ret