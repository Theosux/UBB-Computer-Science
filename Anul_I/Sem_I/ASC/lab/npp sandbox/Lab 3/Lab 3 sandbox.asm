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
    a dd 124
    b db 2
    c dw 15
    d db 200
    e dq 80
; a + b / c - d * 2 - e, fara semn
; our code starts here
segment code use32 class=code
    start:
        ; ...
        ;b / c
        mov AL, [b]     ;Al = b
        mov AH, 0       ;AX = b (fara semn)
        mov DX, 0       ;DX:AX = b
        div word [c]    ;AX = b/c si DX = b%c
        mov BX, AX      ; salvez catul
        
        ;d * 2
        mov AL, 2
        mul byte [d]    ;AX = d*2
        
        ;b / c - d * 2
        sub BX, AX      ;BX = b / c - d * 2
        
        ;a + ...
        ;mov EAX, 0
        ;mov AX, BX      ;EAX = b / c - d * 2
        ;add EAX, [a]    ;EAX = a + b / c - d * 2
        
        mov AX, word [a]    ;AX = cuv inferior
        mov DX, word [a+2]  ;DX:AX = a
        add AX, BX
        mov CX, 0
        adc DX, CX          ;DX:AX = a + b / c - d * 2
        
        push DX             
        push AX
        pop EAX             ;EAX = a + b / c - d * 2
        
        sub EAX 
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
