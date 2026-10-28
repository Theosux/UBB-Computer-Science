bits 32 

global start        


extern exit               
import exit msvcrt.dll    

segment data use32 class=data


segment code use32 class=code
    start:
        mov eax, [ebx*2 + ecx]
    
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
