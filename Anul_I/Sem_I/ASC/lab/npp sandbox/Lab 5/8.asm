bits 32 ; assembling for the 32 bits architecture

global start        

extern exit               
import exit msvcrt.dll    
                          

segment data use32 class=data
    S db 'a', 'A', 'b', 'B', '2', '%', 'x', 'M'
    l equ $-S
    D times l db 0
    
    
;Se da un sir de caractere S. Sa se construiasca sirul D care sa contina toate literele mari din sirul S
;S: 'a', 'A', 'b', 'B', '2', '%', 'x', 'M'
;D: 'A', 'B', 'M'
segment code use32 class=code
    start:
        mov ecx, l
        mov esi, 0
        mov edi, 0
        Parcurgere:
        mov al, [S+esi]
        cmp al, 'A'
        jae pas1
        jmp Next
        pas1:
        cmp al, 'Z'
        jbe pas2
        jmp Next
        pas2:
        mov [D+edi], al
        inc edi
        Next:
        inc esi
        loop Parcurgere
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
