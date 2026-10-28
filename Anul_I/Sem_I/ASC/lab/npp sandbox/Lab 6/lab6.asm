bits 32 ; assembling for the 32 bits architecture


global start        


extern exit               
import exit msvcrt.dll    


segment data use32 class=data
    s db 12h, 13h, 15h, 18h, 22h, 25h, 27h, 30h
    len equ $-s
    s1 times len db 0
    s2 times len db 0
    
segment code use32 class=code
    start:
        mov ecx, len
        mov esi, s
        mov edi, s1
        mov ebx, s2
        cld
        
    parse:
        lodsb
        test al, 1
        jz e_par
    e_impar:
        mov [ebx], al
        inc ebx
        jmp next:
        
    e_par:
        stosb
    next:
        loop parse
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
