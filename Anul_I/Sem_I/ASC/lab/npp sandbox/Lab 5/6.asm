bits 32 ; assembling for the 32 bits architecture

global start        

extern exit               
import exit msvcrt.dll    
                          

segment data use32 class=data
    S db 1, 2, 3, 4, 5, 6, 7, 8
    l equ $-S
    l2 equ ($-S)/2 
    D times l db 0


;Se da un sir de octeti S. Sa se construiasca sirul D astfel: sa se puna mai intai elementele de pe pozitiile pare din S iar apoi elementele de pe pozitiile impare din S
;S: 1, 2, 3, 4, 5, 6, 7, 8
;D: 1, 3, 5, 7, 2, 4, 6, 8
segment code use32 class=code
    start:
        mov ecx, l
        mov esi, 0
        mov edi, 0
        mov edx, 0
        jecxz final
        Parcurge:
            mov al, [S+edx]
            test edx, 1
            je par
            mov [D+esi+l2], al
            inc esi
            jmp next
            par:
            mov [D+edi], al
            inc edi
            next:
            INC edx
            loop Parcurge
            
        
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
