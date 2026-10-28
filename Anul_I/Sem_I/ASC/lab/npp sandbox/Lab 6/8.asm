bits 32 ; assembling for the 32 bits architecture

global start        


extern exit               
import exit msvcrt.dll    



segment data use32 class=data
    S DD 12345678h, 1A2C3C4Dh, 98FCDC76h
    l equ ($-S)/4
    D times l db 0

; 11011101 01100110 11111101 00000000b, 11011101 11100111 11111101 00000000b, 11011101 01000010 11111101 00000000b
;Se da sirul de dublucuvinte:
;s DD 12 34 5678h, 1A 2C 3C4Dh, 98 FC DC76h
;Sa se obtina sirul
;d DB 2Ch, FCh.

;Se da un sir de dublucuvinte. Sa se obtina sirul format din octetii inferiori ai
;cuvintelor superioare din elementele sirului de dublucuvinte care sunt palindrom in scrierea in baza 10.
segment code use32 class=code
    start:
        mov ecx, l
        mov esi, S
        mov edi, D
        jecxz Final
        Parcurgere:
        lodsw
        lodsb   ; al - octetul
        mov bl, al
        mov bh, al
        shr bh, 4   ; primul nibble ( 0000 xxxx )
        shl bl, 4
        shr bl, 4   ; al doilea nibble ( 0000 abcd )
        
        ;oglindim al doilea nibble:
        xor dl, dl  ; in dl avem varianta finala
        mov ah, bl  ; lucram cu copie
        and ah, 00000001b ;b1
        shl ah, 3         ;pe poz 4
        or dl, ah
        mov ah, bl
        and ah, 00000010b ;b2
        shl ah, 1         ;pe poz 3
        or dl, ah
        mov ah, bl  
        and ah, 00000100b ;b3
        shr ah, 1         ;pe poz 2
        or dl, ah
        mov ah, bl
        and ah, 00001000b ;b2
        shr ah, 3         ;pe poz 1
        or dl, ah
        mov bl, dl
        
        ;comparam cei doi nibble
        cmp bl, bh
        jne sari
        stosb
        sari:
        lodsb
        loop Parcurgere
        Final:
    
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
