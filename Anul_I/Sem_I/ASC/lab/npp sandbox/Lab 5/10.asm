bits 32 ; assembling for the 32 bits architecture

global start        

extern exit               
import exit msvcrt.dll    
                          

segment data use32 class=data
    S1 db '+', '2', '2', 'b', '8', '6', 'X', '8'
    l1 equ $-S1
    S2 db 'a', '4', '5'
    l2 equ $-S2
    D times l1+l2 db 0
    


;Se dau doua siruri de caractere S1 si S2. Sa se construiasca sirul D prin concatenarea 
;elementelor sirului S2 in ordine inversa cu elementele de pe pozitiile pare din sirul S1.
;S1: '+', '2', '2', 'b', '8', '6', 'X', '8'
;S2: 'a', '4', '5'
;D: '5', '4', 'a', '2','b', '6', '8'
segment code use32 class=code
    start:
        mov ecx, l2
        mov esi, 0
        jecxz final2
        Parcurgere2:
            mov al, [S2+ecx-1]
            mov [D+esi], al
            inc esi
        loop Parcurgere2
        final2:
        mov ecx, l1/2
        mov esi, 1
        mov edi, 0
        jecxz final1
        Parcurgere1:
            mov al, [S1+esi]
            mov [D+l2+edi], al
            add esi, 2
            inc edi
        loop Parcurgere1
        final1:
    
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
