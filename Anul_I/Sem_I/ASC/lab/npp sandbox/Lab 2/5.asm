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
e DW 1345h
f DW 1B2Ch
g DW 321Eh



; (e+f)*g
; (1345h + 1B2Ch) * 321Eh


; our code starts here
segment code use32 class=code
    start:
        ; ...
    XOR EAX, EAX
    XOR EDX, EDX
    MOV AX, [e] ;AX=e
    ADD AX, [f] ;AX=e+f
    MOV DX, [g] ;DX=g
    MUL DX      ;DX:AX=AX*DX
    
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
