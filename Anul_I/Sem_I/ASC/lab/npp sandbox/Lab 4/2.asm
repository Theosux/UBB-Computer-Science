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
    a dw 0110_1000_0100_1111b
    b dw 0100_0110_0011_0001b
    c dd 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        ;bitii 0-3 ai lui C coincid cu bitii 5-8 ai lui B
        ;bitii 4-8 ai lui C coincid cu bitii 0-4 ai lui A
        ;bitii 9-15 ai lui C coincid cu bitii 6-12 ai lui A
        ;bitii 16-31 ai lui C coincid cu bitii lui B
        MOV DX, [b]
        MOV EBX, 0           ; c = 0000 0000 0000 0000 0000 0000 0000 0000
        MOV AX, [b]
        AND AX, 0000_0001_1110_0000b
        MOV CL, 5
        SHR AX, CL
        OR BX, AX
        MOV AX, [a]
        AND AX, 0000_0000_0001_1111b
        MOV CL, 4
        SHL AX, CL
        OR BX, AX
        MOV AX, [a]
        AND AX, 0001_1111_1100_0000b
        MOV CL, 3
        SHL AX, CL
        OR BX, AX
        push DX
        push BX
        pop EBX
        mov [c], EBX
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
