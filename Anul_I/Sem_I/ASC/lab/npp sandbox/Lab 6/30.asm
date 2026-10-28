bits 32 ; assembling for the 32 bits architecture

global start

extern exit
import exit msvcrt.dll

segment data use32 class=data
    S dw 07A2h, 1206h, 0101h
    l equ ($ - S) / 2
    s1 times l db 0
    s2 times l db 0

    
;Se da un sir de cuvinte. Sa se construiasca doua siruri de octeti, s1 si s2, astfel: pentru fiecare cuvant,
;daca numarul de biti 1 din octetul high al cuvantului este mai mare decat numarul de biti 1 din octetul low,
;atunci s1 va contine octetul high, iar s2 octetul low al cuvantului
;daca numarul de biti 1 din cei doi octeti ai cuvantului sunt egali,
;atunci s1 va contine numarul de biti 1 din octet, iar s2 valoarea 0
;altfel, s1 va contine octetul low, iar s2 octetul high al cuvantului.    
segment code use32 class=code
start:
    mov ecx, l
    cld
    mov esi, S
    xor bh, bh          ; incrementator de pozitie

Parcurgere:
    lodsw           ; ah - high, al - low
    push ax         ; salvam ax

    
    mov bl, 8       ; bl = 8
    xor dl, dl      ; dl = 0
    xor dh, dh      ; dh = 0
    Numararel:
        test al, 00000001b
        jz skip_low
        inc dl
    skip_low:
        shr al, 1
        dec bl
        jnz Numararel

        
        mov bl, 8             
    Numarareh:
        test ah, 00000001b
        jz skip_high
        inc dh
    skip_high:
        shr ah, 1
        dec bl
        jnz Numarareh

        pop ax          

        ;transformam bh in ebx
        mov bl, 0
        shl ebx, 16
        shr ebx, 24
        
        cmp dh, dl
        ja caz1         
        je caz2         
        jb caz3         

    ; Caz 1 dh > dl
    caz1:
        mov edi, s2
        add edi, ebx
        stosb
        mov edi, s1     
        add edi, ebx
        mov al, ah
        stosb
        jmp next_word

    ; Caz 2 dh = dl
    caz2:
        mov edi, s1
        add edi, ebx
        mov al, dl
        stosb           ; am pus dl (nr biti 1) in s1
        xor al, al      
        mov edi, s2
        add edi, ebx
        stosb           ; am pus 0 in s2
        jmp next_word

    ; Caz 3 dh < dl
    caz3:
        mov edi, s1
        add edi, ebx
        stosb
        mov edi, s2     
        add edi, ebx
        mov al, ah
        stosb

    next_word:
        inc ebx
        ;punem ebx in bh
        shl ebx, 8
        loop Parcurgere

    push dword 0
    call [exit]
