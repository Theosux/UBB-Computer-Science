bits 32 ; assembling for the 32 bits architecture

global start        

extern exit               
import exit msvcrt.dll    


segment data use32 class=data
    S db 5, 25, 55, 127
    l equ $-S
    D times l db 0



;s: 5, 25, 55, 127

;binar:
;101, 11001,10111,1111111

;d: 2, 3, 5, 7

;Se da un sir de octeti s. Sa se construiasca sirul de octeti d,
;care contine pe fiecare pozitie numarul de biti 1 ai octetului de pe pozitia corespunzatoare din s.
segment code use32 class=code
    start:
        mov ecx, l
        mov esi, S
        mov edi, D
        jecxz Final
        Parcurge:
            lodsb       ; al = nr
            xor ah, ah  ; ah = 0, cnt
            Numarare:
                test al, 00000001b
                jz sari
                inc ah
                sari:
                shr al, 1
                jnz Numarare
            mov al, ah
            stosb
            loop Parcurge
        Final:
    

        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
