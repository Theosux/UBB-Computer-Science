bits 32 ; assembling for the 32 bits architecture

global start        

extern exit               
import exit msvcrt.dll    


segment data use32 class=data
    S dd 12345678h, 782B3C4Dh, 06698DC76h
    l equ ($-S)/4
    D times l db 0

;Se da sirul de dublucuvinte:
;s DD 12 34 5678h, 1A 2B 3C4Dh, FE 98 DC76h
;Sa se obtina sirul
;d DB 12h.

;Se da un sir de dublucuvinte. Sa se obtina sirul format din octetii superiori ai
;cuvitelor superioare din elementele sirului de dublucuvinte care sunt divizibili cu 3.
segment code use32 class=code
    start:
        mov ecx, l
        mov esi, S
        mov edi, D
        Parcurgere:
            lodsw
            lodsb
            lodsb
            mov BH, AL
            movzx AX, AL
            mov BL, 3
            div BL
            cmp AH, 0
            jne sari
            mov AL, BH
            stosb 
            sari:
            loop Parcurgere
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
