bits 32 ; assembling for the 32 bits architecture

global start        


extern exit               
import exit msvcrt.dll    



segment data use32 class=data
    S dd 12345678h, 1A2C3C4Dh, 98FCDD76h, 12783A2Bh
    l equ ($-S)/4
    D dd 0

;Se da sirul de dublucuvinte:
;s DD 1234 56 78h, 1A2C 3C 4Dh, 98FC DD 76h, 1278 3A 2Bh
;Sa se obtina dublucuvant
;d DD FF3A3C56h.

;Se da un sir de dublucuvinte.
;Sa se obtina, incepand cu partea inferioara a dublucuvantului,
;dublucuvantul format din octetii superiori pari ai cuvintelor inferioare din elementele sirului de dublucuvinte.
;Daca nu sunt indeajuns octeti se va completa cu octetul FFh.
segment code use32 class=code
    start:
        mov ecx, l
        mov esi, S
        mov edi, D
        jecxz Final
        xor ebx, ebx      ; cnt
        Parcurgere:
            lodsb
            lodsb   ; al - octetul smecher
            test al, 00000001b
            jz par
            inc ebx
            jmp next
            par:
                stosb
            next:
                lodsw
                loop Parcurgere
        mov ecx, ebx
        jecxz Final
        Umplere:
            mov al, 0FFh
            stosb
                loop Umplere
        Final:
    
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
