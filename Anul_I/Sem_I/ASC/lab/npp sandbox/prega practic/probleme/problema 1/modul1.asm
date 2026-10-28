bits 32 

global _modul1        
  

segment data public data use32

;Se da un numar a reprezentat pe 32 biti fara semn.
;Se cere sa se afiseze reprezentarea in baza 16 a lui a,
;precum si rezultatul permutarilor circulare ale cifrelor sale.

segment code public code use32
    _modul1:
    
    push ebp
    mov ebp, esp
    
    push ebx
    push edi
    
    mov eax, [ebp+8]
    mov edi, [ebp+12]
    
    mov ebx, 16
    xor ecx, ecx
    
    bucla_impartire:
        xor edx, edx
        div ebx
        
        push edx
        inc ecx
        
        test eax, eax
        jne bucla_impartire
    
    xor ebx, ebx
    afisare:
        pop eax
        
        cmp eax, 9
        ja litera
        
        add eax, '0'
        jmp adauga
        
        litera:
        add eax, 55
        
        adauga:
        stosb
        inc ebx
    loop afisare
    
    mov byte [edi], 0
    mov eax, ebx
    
    pop edi
    pop ebx
    
    mov esp, ebp
    pop ebp
    
    ret
