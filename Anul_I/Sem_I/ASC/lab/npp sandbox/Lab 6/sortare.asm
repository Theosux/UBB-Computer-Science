bits 32 ; assembling for the 32 bits architecture

global start        

extern exit               
import exit msvcrt.dll
        ;.....
        ;.....
        D times l db 0


segment data use32 class=data

segment code use32 class=code
    start:
        ; Sortare D cu semn:
            mov ecx, l
            dec ecx
            jecxz Final
            loop1:
                mov esi, D
                mov DH, 0 ;flag de sortare
                mov ebx, ecx
            loop2:
                mov al, [esi]
                cmp al, [esi+1]
                jle Continua
                mov dl,[esi+1]
                mov [esi], dl
                mov [esi+1], al
                mov dh, 1
            Continua:
                inc esi
                dec ebx
                jnz loop2
                
                cmp dh, 0
                je Final
                
                dec ecx
                jnz loop1
        Final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
