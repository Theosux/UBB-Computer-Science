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
a DB 0A7h
b DB 032h
c DB 01Ah
d DW 1325h



;((a+b-c)*2 + d-5)*d
; ((0A7h + 032h - 01Ah )*2 + ('ab'-5))*'ab'


; our code starts here
segment code use32 class=code
    start:
        ; ...
    XOR EAX, EAX
    XOR EDX, EDX
    MOV AL, [a] ;AL=a
    ADD AL, [b] ;AL=a+b
    SUB AL, [c] ;AL=a+b-c
    MOV DX, [d] ;DX=d
    SUB DX, 5   ;DX=d-5
    MOV BL, 2   ;BL=2
    MUL BL      ;AX=(a+b-c)*2
    ADD AX, DX  ;AX=((a+b-c)*2 + d-5)
    MOV BX, [d] ;BX=[d]
    MUL BX      ;DX:AX = ((a+b-c)*2 + d-5)*d
    
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
