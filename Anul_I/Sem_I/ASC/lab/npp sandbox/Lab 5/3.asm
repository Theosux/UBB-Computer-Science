bits 32 ; assembling for the 32 bits architecture


global start        


extern exit               
import exit msvcrt.dll    
                          


segment data use32 class=data
    S1 db 1, 2, 3, 4
    l1 equ $-S1
    S2 db 5, 6, 7
    l2 equ $-S2
    D times l1+l2 db 0
    
;Se dau doua siruri de octeti S1 si S2. Sa se construiasca sirul D prin concatenarea elementelor din sirul S1 1uate de la stanga spre dreapta si a elementelor din sirul S2 luate de la dreapta spre stanga.
;S1: 1, 2, 3, 4
;S2: 5, 6, 7
;D: 1, 2, 3, 4, 7, 6, 5
segment code use32 class=code
    start:
        mov ecx, l1
        mov esi, 0
        jecxz Final
        Parcurgere1:
            mov al, [S1+esi]
            mov [D+esi], al
            INC esi
            loop Parcurgere1
        mov ecx, l2
        mov esi, l2-1
        mov edi, l1
        Parcurgere2:
            mov al, [S2+esi]
            mov [D+edi], al
            DEC esi
            INC edi
            loop Parcurgere2
        Final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
