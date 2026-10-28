bits 32 

global _modul2     

segment data public data use32

segment code public code use32
    _modul2:
        push ebp
        mov ebp, esp
        
        push esi
        mov esi, [ebp+8]
        
        mov al, [esi]
        cmp al, 0
        je final
        
        bucla_permutare:
        
            mov dl, [esi+1]
            test dl, dl
            je final
            
            mov [esi], dl
            inc esi
            
        jmp bucla_permutare
        
        final:
            mov [esi], al
            
        pop esi
        mov esp, ebp
        pop ebp
    ret
    
