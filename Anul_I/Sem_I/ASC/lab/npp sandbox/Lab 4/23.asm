bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    a db 0110_1000b
    b dw 0111_1010_0001_1000b
    c dd 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
    ;bitii 24-31 ai lui C sunt bitii lui A
    ;bitii 16-23 ai lui C sunt inversul bitilor din octetul cel mai putin semnificativ al lui B
    ;bitii 10-15 ai lui C sunt 1
    ;bitii 2-9 ai lui C sunt bitii din octetul cel mai semnificativ al lui B
    ;bitii 0-1 se completeaza cu valoarea bitului de semn al lui A
    
    ;formez dublucuvantul c in registrii DX:AX
        MOV DX, 0
        MOV AX, 0
    ;bitii 24-31 ai lui C sunt bitii lui A
        MOV DH, [a]
    ;bitii 16-23 ai lui C sunt inversul bitilor din octetul cel mai putin semnificativ al lui B
        MOV BL, [b]
        NOT BL
        MOV DL, BL
    ;bitii 10-15 ai lui C sunt 1
        OR AX, 1111_1100_0000_0000b
    ;bitii 2-9 ai lui C sunt bitii din octetul cel mai semnificativ al lui B
        MOV BX, [b]
        SHL BX, 2
        OR AX, BX
    ;bitii 0-1 se completeaza cu valoarea bitului de semn al lui A
        MOV BL, [a]
        AND BL, 1000_0000b
        SHR BL, 6
        OR AL, BL
        SHR BL, 1
        OR AL, BL
        
        mov [c], AX
        mov [c+2], DX
    
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
