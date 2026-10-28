bits 32 ; assembling for the 32 bits architecture

global start        

extern exit               
import exit msvcrt.dll    
                          

segment data use32 class=data
    S dw -22, 145, -48, 127
    l equ ($-S)/2
    D times l db 0
    
;s: -22, 145, -48, 127
;in binary:
;1111111111101010, 10010001, 1111111111010000, 1111111
;d: 3, 3, 5, 7

;Se da un sir de cuvinte s. Sa se construiasca sirul de octeti d, astfel incat d sa contina pentru fiecare pozitie din s:
;- numarul de biti de 0, daca numarul este negativ
;- numarul de biti de 1, daca numarul este pozitiv
segment code use32 class=code
    start:
        mov ecx, l
        mov esi, S
        mov edi, D
        jecxz Final
        Parcurge:
            lodsw       ; ax = nr
            xor bh, bh  ; - cnt
            cmp ax, 0
            jl Numarareneg
            Numararepoz:
                test ax, 0000000000000001b
                jz sari1
                inc bh
                sari1:
                shr ax, 1
                jnz Numararepoz
            jmp next
            Numarareneg:
                test ax, 0000000000000001b
                jnz sari2
                inc bh
                sari2:
                shr ax, 1
                jnz Numarareneg
            next:
            ;in bh se regaseste nr dorit
            mov al, bh
            stosb
            loop Parcurge
        Final:
    
    
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
