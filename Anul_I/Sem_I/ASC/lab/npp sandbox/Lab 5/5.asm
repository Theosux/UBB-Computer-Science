bits 32 ; assembling for the 32 bits architecture

global start        

extern exit               
import exit msvcrt.dll    
                          

segment data use32 class=data
    S db 'a', 'A', 'b', 'B', '2', '%', 'x'
    l equ $-S
    D times l db 0
    
    
;Se da un sir de caractere S. Sa se construiasca sirul D care sa contina toate literele mici din sirul S.
;S: 'a', 'A', 'b', 'B', '2', '%', 'x'
;D: 'a', 'b', 'x'
segment code use32 class=code
    start:
        mov ecx, l
        mov esi, 0
        mov edi, 0
        jecxz final
        Parcurge:
        mov al, [S+esi]
        cmp al, 'a'
        jae pas1 ;>=a
        jmp next
        pas1:
        cmp al, 'z'
        jbe pas2 ;<=z
        jmp next
        pas2:
        mov [D+edi], al
        INC edi
        next:
        INC esi
        loop Parcurge
        final:
    

        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
