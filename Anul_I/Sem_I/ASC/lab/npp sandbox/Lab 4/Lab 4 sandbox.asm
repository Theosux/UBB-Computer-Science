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
     a dw 0111011101010111b
     b dw 1001101110111110b
     c dw 0
; our code starts here
segment code use32 class=code
    start:
        ; ...
    ; Se dau cuvintele A si B. Se cere cuvantul C format astfel:
    ;- bitii 0-2 ai lui C coincid cu bitii 10-12 ai lui B
    ;- bitii 3-6 ai lui C au valoarea 1
    ;- bitii 7-10 ai lui C coincid cu bitii 1-4 ai lui A
    ;- bitii 11-12 ai valoarea 0
    ;- bitii 13-15 ai lui C concid cu inverul bitilor 9-11 ai lui B
    
    
    
        ;formez c in registrul BX
        MOV BX, 0           ; c = 0000000000000000b
        MOV AX, [b]
        AND AX, 0001_1100_0000_0000b
        MOV CL, 10
        SHR AX, CL ; nr de deplasari se tine in CL
        OR BX, AX           
        OR BX, 0000_0000_0111_1000b         ; bitii 3-6 devin unu
        MOV DX, [a]
        ;bitii 7-10 ai lui C coincid cu bitii 1-4 ai lui A
        and DX, 0000_0000_0001_1110b
        SHL DX, 6
        OR BX, DX           ; c = 0000 0AAA A111 1BBB
        
        ;bitii 11-12 iau valoarea 0
        
        and BX, 1110_01111_1111_1111b
        
        ; bitii 13-15 ai lui C concid cu inverul bitilor 9-11 ai lui B
        
        MOV AX [b]
        NOT AX
        AND AX, 0000_1110_0000_0000b
        SHL AX, 4
        OR BX, AX           
        MOV [c], BX
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
