bits 32

global _modul1

segment data public data use32

segment code public code use32
    _modul1:
        ; cod intrare
        push ebp
        mov ebp, esp
        push ebx
        
        mov ebx, [ebp+8]    ; index primul sir
        mov eax, [ebp+12]   ; index al doilea sir
        mov edx, [ebp+16]   ; lungime primul sir
        mov ecx, [ebp+20]   ; lungime al doilea sir
        
        mov esi, eax        ; parcurgem al doilea sir
        xor eax, eax
        parcurgere:
            mov byte al, [esi]
            mov byte ah, [ebx]
            cmp al,ah
            je litera
            ;reset
            
            ; mov ebx, [ebp+8]
            ; mov edx, [ebp+16]
            ; jmp sari1
            
            mov eax, [ebp+16]   ; lungimea initiala
            sub eax, edx        ; cate caractere am potrivit
            
            sub esi, eax        ; mergem inapoi atatia pasi
            add ecx, eax
            
            mov ebx, [ebp+8]
            mov edx, [ebp+16]
            jmp sari1
            litera:
                dec edx
                inc ebx
            sari1:    
            
            cmp edx, 0
            je gasit
            inc esi
            loop parcurgere
        
        mov eax, 0
        jmp sari2
        gasit:
            mov eax, 1
        sari2:
        
        ; cod iesire
        pop ebx
        mov esp, ebp
        pop ebp
        
        ret