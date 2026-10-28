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
a DW 2031h
b DW 1243h
c DW 0D659h
d DW 0A321h


;(c+b+a)-(d+d)
;(D659h+1243h+2031h)-(A321h+A321h)


; our code starts here
segment code use32 class=code
    start:
        ; ...
MOVZX EAX, WORD [a]   ; EAX=a
MOVZX EBX, WORD [b]   ; EBX=b
ADD   EAX, EBX        ; EAX=a+b
MOVZX EBX, WORD [c]   ; EBX=c
ADD   EAX, EBX        ; EAX=a+b+c
MOVZX EBX, WORD [d]   ; EBX=d
ADD   EBX, EBX        ; EBX=d+d
SUB   EAX, EBX        ; EAX=(a+b+c)-(d+d)
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
