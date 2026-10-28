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
    a db 03h
    b dd 02h
    c dq 100h
    ;c+(a*a-b+7)/(2+a)
; our code starts here
segment code use32 class=code
    start:
        ; ...
    MOV AL, [a]         ; AL=a
    CBW                 ; AX=a
    IMUL AL             ; AX=a*a
    CWDE                ; EAX=a*a
    SUB EAX, [b]        ; EAX=a*a-b
    ADD EAX, 7          ; EAX=a*a-b+7
    MOV BL, [a]         ; BL=a
    MOVZX EBX, BL       ; EBX=a
    ADD EBX, 2          ; EBX=a+2
    CDQ                 ; EDX:EAX=a*a-b+7
    IDIV EBX            ; EAX=(a*a-b+7) / (2+a)
    MOV EBX, EAX        ; EBX=(a*a-b+7) / (2+a)
    MOV EAX, dword [c]
    MOV EDX, dword [c+4]; EDX:EAX=c
    ADD EAX, EBX        
    ADC EDX, 0          ; EDX:EAX=c+(a*a-b+7) / (2+a)
    
    
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
