bits 32 ; assembling for the 32 bits architecture


global start        


extern exit              
import exit msvcrt.dll    
                          

segment data use32 class=data
    S db 1, 6, 3, 1
    l equ $-S
    D times l-1 db 0

;Se da un sir de octeti S de lungime l. Sa se construiasca sirul D de lungime l-1 astfel incat elementele 
;din D sa reprezinte catul dintre fiecare 2 elemente consecutive S(i) si S(i+1) din S.
;S: 1, 6, 3, 1
;D: 0, 2, 3
segment code use32 class=code
    start:
        mov ecx, l-1
        mov esi, 0
        jecxz final
        repeta:
        movzx ax, [S+esi]
        mov bl, [S+esi+1]
        div bl  ; al - cat, ah - rest
        mov [D+esi], al
        inc esi
        dec ecx
        cmp ecx, 0
        jne repeta
        final:
    

        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
