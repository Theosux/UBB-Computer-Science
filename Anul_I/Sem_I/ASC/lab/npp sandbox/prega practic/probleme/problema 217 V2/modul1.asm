bits 32

global _modul1
extern _modul2

segment data public data use32
nr_c dd 0
nr dd 0
segment code public code use32
    _modul1:
    ;codul de intrare
    push ebp
    mov ebp, esp
    push ebx 
    push esi
    push edi
    
    mov dword [nr_c], 0
    mov dword [nr], 0
    
    mov esi, [ebp+8]
    
    bucla:
        lodsd
        cmp eax, 0
        je iesi
        mov edx, eax        ; salvam nr
        push eax
        push edx
        call _modul2
        add esp, 4
        pop edx
        
        mov ebx, [nr_c]
        cmp eax, ebx
        jng sari
        mov [nr_c], eax
        mov [nr], edx
        sari:
        jmp bucla
    
    iesi:
        mov eax, [nr]
    
    ;codul de iesire
    pop edi
    pop esi
    pop ebx
    mov esp, ebp
    pop ebp
    ret