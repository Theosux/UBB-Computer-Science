bits 32 ; assembling for the 32 bits architecture

global start        

extern exit               
import exit msvcrt.dll    
                          

segment data use32 class=data
    S1 db 1, 2, 3, 4
    l equ $-S1
    S2 db 5, 6, 7, 8
    D times l db 0

;Se dau doua siruri de octeti S1 si S2 de aceeasi lungime. Sa se construiasca sirul D astfel: fiecare element de pe pozitiile pare din D este suma elementelor de pe pozitiile corespunzatoare din S1 si S2, iar fiecare element de pe pozitiile impare are ca si valoare diferenta elementelor de pe pozitiile corespunzatoare din S1 si S2.
;S1: 1, 2, 3, 4
;S2: 5, 6, 7, 8
;D: 6, -4, 10, -4
segment code use32 class=code
    start:
        mov ecx, l
        mov esi, 0
        jecxz final
        Parcurge:
            test esi, 1 ;ZF = 1 pt nr par
            je par
            ;caz impar
            mov al, [S1+esi]
            sub al, [S2+esi]
            mov [D+esi], al
            jmp next
            par:
            mov al, [S1+esi]
            add al, [S2+esi]
            mov [D+esi], al
            next:
            INC esi
            loop Parcurge
            final:

        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
