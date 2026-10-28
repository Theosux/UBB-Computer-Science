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
a DB 23h
b DB 13h
c DB 0D9h
d DB 0A1h


;c-(a+d)+(b+d)
;D9h-(23h+A1h)+(13h+A1h)

    
; our code starts here
segment code use32 class=code
    start:
        ; ...
    MOV AH, 0
    MOV AL, [c]     ; AL = c
    MOV BX, [a]     ; BX = a
    ADD BX, [d]     ; BX = a + d
    SUB AX, BX      ; AX = c - (a + d)
    MOV BX, [b]     ; BL = b
    ADD BX, [d]     ; BL = b + d
    ADD AX, BX      ; AX = c - (a+d) + (b+d)
    
    
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
