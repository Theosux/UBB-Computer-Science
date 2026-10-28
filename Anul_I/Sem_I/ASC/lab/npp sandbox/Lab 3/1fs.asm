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
    a DB 12h
    b DW 1321h
    c DD 215A20h
    d DQ 1321h
    x resq 1

; c-(a+d)+(b+d)
segment code use32 class=code
    start:
        ; ...
        
        ;a + d
        mov EAX, 0
        mov AL, [a]     ;EAX = a
        mov EDX, 0      ;EDX:EAX = a
        mov ECX, [d]
        mov EBX, [d+4]  ;EBX:ECX = d
        add EAX, ECX
        adc EDX, EBX    ;EDX:EAX = a + d
        
        ;c - (a + d)
        mov ECX, [c]
        mov EBX, 0      ;EBX:ECX = c
        sub ECX, EAX
        sbb EBX, EDX    ;EBX:ECX = c - (a + d)
        mov [x], ECX
        mov [x+4], EBX  ;x = c - (a + d)
        
        ;b + d
        mov EAX, 0
        mov AX, [b]     ;EAX = b
        mov EDX, 0      ;EDX:EAX = b
        mov ECX, [d]
        mov EBX, [d+4]  ;EBX:ECX = d
        add EAX, ECX
        adc EDX, EBX    ;EDX:EAX = b + d
        
        ;c - (a + d) + (b + d)
        mov ECX, [x]
        mov EBX, [x+4]
        add ECX, EAX
        adc EBX, EDX    ;EBX:ECX = c - (a + d) + (b + d)
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
