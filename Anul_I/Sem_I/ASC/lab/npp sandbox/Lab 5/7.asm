bits 32 ; assembling for the 32 bits architecture

global start        

extern exit               
import exit msvcrt.dll    
                          

segment data use32 class=data
    S1 db 1, 3, 5, 7
    l equ $-S1
    S2 db 2, 6, 9, 4
    D times (l*2) db 0


;Se dau doua siruri de octeti S1 si S2 de aceeasi lungime. Sa se obtina sirul D prin intercalarea elementelor celor doua siruri
;S1: 1, 3, 5, 7
;S2: 2, 6, 9, 4
;D: 1, 2, 3, 6, 5, 9, 7, 4
segment code use32 class=code
    start:
        mov ecx, l
        mov esi, 0
        mov edi, 0
        jecxz Final
        Parcurgere:
            mov al, [S1+esi]
            mov bl, [S2+esi]
            mov [D+edi], al
            mov [D+edi+1], bl
            inc esi
            add edi, 2
        loop Parcurgere
        Final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
