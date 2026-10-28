bits 32 ; assembling for the 32 bits architecture

global start        

extern exit, scanf, printf               
import exit msvcrt.dll    
import scanf msvcrt.dll    
import printf msvcrt.dll    


segment data use32 class=data
    msg db "Dati un cuvant: ", 0
    s1 times 50 db 0                ; aloc spatiu de stocare pt sir
    read_format db "%s", 0

segment code use32 class=code
    start:
    read:
        ; afisez mesaj
        ; printf (msg)
        push msg
        call [printf]
        add esp, 1*4
        
        ; citesc un sir de caractere
        ; scanf("%s", s1)
        push s1
        push read_format
        call [scanf]
        add esp, 2*4
        
        ; verific conditia de oprire
        cmp byte [s1], '!'
        je stop
        
        jmp read
        
    stop:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
