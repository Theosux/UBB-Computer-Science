bits 32 ; assembling for the 32 bits architecture

global start        

extern exit               
import exit msvcrt.dll    
                          

;Se da un sir de caractere S. Sa se construiasca sirul D care sa contina toate caracterele speciale (!@#$%^&*) din sirul S.
segment data use32 class=data
    S db '+', '4', '2', 'a', '@', '3', '$', '*'
    l equ $-S
    D times l db 0
    


segment code use32 class=code
    start:
        mov ecx, l
        mov esi, 0
        mov edi, 0
        jecxz Sfarsit
        Parcurgere:
        mov al, [S+esi]
        cmp al, '!'
        je PuneInD
        cmp al, '@'
        je PuneInD
        cmp al, '#'
        je PuneInD
        cmp al, '$'
        je PuneInD
        cmp al, '%'
        je PuneInD
        cmp al, '^'
        je PuneInD
        cmp al, '&'
        je PuneInD
        cmp al, '*'
        je PuneInD
        jmp maiDeparte
        PuneInD:
            mov [D+edi], al
            INC edi
        maiDeparte:
            INC esi
            loop Parcurgere
        Sfarsit:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
