bits 32 ; assembling for the 32 bits architecture

global start        

extern exit               
import exit msvcrt.dll    
                          


segment data use32 class=data
    S db 1, 2, 3, 4
    l equ $-S
    D times l-1 dw 0
    
    
;Se da un sir de octeti S de lungime l. Sa se construiasca sirul D de lungime l-1 astfel incat elementele din D sa reprezinte produsul dintre fiecare 2 elemente consecutive S(i) si S(i+1) din S.
segment code use32 class=code
    start:
        mov ecx, l-1
        mov esi, 0
        jecxz sfarsit
        Repeta:
            mov al, [S+esi]
            mov bl, [S+esi+1]
            mul bl  ; AX = AL * BL
            mov [D+esi], ax 
            INC esi
            loop Repeta
        sfarsit:
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
