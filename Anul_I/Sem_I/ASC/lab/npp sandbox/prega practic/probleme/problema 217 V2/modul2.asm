bits 32

global _modul2

segment data public data use32

segment code public code use32
    _modul2:
    ;codul de intrare
    push ebp
    mov ebp, esp
    push ebx
    push ecx
    
    ;parte logica
    mov eax, [ebp+8]
    
    cmp eax, 0
    jge sari
    neg eax
    
    sari:
    
    mov ebx, 10
    xor ecx, ecx        ;contor cifre impare
    bucla:
        xor edx, edx
        div ebx
        test edx, 1
        
        jz par
        inc ecx
        
        par:
        
        cmp eax, 0
        jnz bucla
    mov eax, ecx
    
    ;codul de iesire
    pop ecx
    pop ebx
    mov esp, ebp
    pop ebp
    ret