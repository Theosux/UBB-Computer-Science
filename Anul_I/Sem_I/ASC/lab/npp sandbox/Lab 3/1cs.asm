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
    a db 80h
    b dw 120h
    c dd 200h
    d dq 300h
    ;(c+b+a)-(d+d)
; our code starts here
segment code use32 class=code
    start:
        ; ...
    MOV AL, [a]         ; AL = a
    CBW                 ; AX = a
    ADD AX, [b]         ; AX = a+b
    CWD                 ; DX:AX = a+b
    MOV BX, [c]
    MOV CX, [c+2]       ; CX:DX = c
    ADD AX, DX
    ADC DX, CX          ; DX:AX = a+b+c
    push DX
    push AX
    pop EAX             ; EAX = (a+b+c)
    CDQ                 ; EDX:EAX = (a+b+c)
    MOV EBX, [d]
    MOV ECX, [d+4]      ; ECX:EBX = d
    ADD EBX, EBX
    ADC ECX, ECX        ; ECX:EBX = d+d
    SUB EAX, EBX
    SBB EDX, ECX        ; EDX:EAX =(c+b+a)-(d+d)
    
    
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
