bits 32

global _modul2

segment data public data use32

segment code public code use32
    _modul2:
        ;cod intrare
        push ebp
        mov ebp, esp
        
        push edi
        mov eax, [ebp+8]
        mov edi, [ebp+12]
        
        mov ebx, 2
        xor ecx, ecx
        bucla:
            xor edx, edx
            div ebx
            
            push edx
            inc ecx
            
            test eax, eax
            jne bucla
        xor ebx, ebx
        formare_nr:
            pop eax
            add eax, '0'
            stosb
            inc ebx
            loop formare_nr
        
        mov byte [edi], 0
        mov eax, ebx
        
        ;cod iesire
        pop edi
        mov esp, ebp
        pop ebp
        ret