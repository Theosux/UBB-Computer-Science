bits 32 ; assembling for the 32 bits architecture

global start        

extern exit               
import exit msvcrt.dll    
                          

segment data use32 class=data
    S db 1, 2, 4, 6, 10, 20, 25
    l equ $-S
    D times l-1 db 0


;Se da un sir de octeti S de lungime l. Sa se construiasca sirul D de lungime l-1 astfel 
;incat elementele din D sa reprezinte diferenta dintre fiecare 2 elemente consecutive din S.
;S: 1, 2, 4, 6, 10, 20, 25
;D: 1, 2, 2, 4, 10, 5
segment code use32 class=code
    start:
        mov ecx, l-1
        mov esi, 0
        Parcurge:
            mov al, [S+esi]
            mov bl, [S+esi+1]
            sub bl, al
            mov [D+esi], bl
            inc esi
            loop Parcurge
    
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
