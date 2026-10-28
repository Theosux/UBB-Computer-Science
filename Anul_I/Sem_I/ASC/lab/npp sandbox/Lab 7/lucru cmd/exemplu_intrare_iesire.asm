bits 32 ; assembling for the 32 bits architecture


global start        


extern exit, scanf, printf, getchar               
import exit msvcrt.dll    
import scanf msvcrt.dll    
import printf msvcrt.dll    
import getchar msvcrt.dll    


segment data use32 class=data
    n dd 0                              ; aloc spatiu de stocare pt numar
    read_format db "%d", 0              ; definesc formatul de citire pt numar
    char_format db "%c", 0              ; definesc formatul de citire pt caracter
    print_format db "Am citit numarul %d si litera %c", 0    ; definesc formatul de afisare
    msg1 db "Introdu un numar: ", 0
    msg2 db "Introdu o litera: ", 0
    c1 db 0                             ; aloc spatiu de stocare pt litera
    
segment code use32 class=code
    start:
        ; afisez un mesaj
        ; printf(msg1)
        push dword msg1
        call [printf]
        add esp, 1*4
        
        
        ; citesc un nr intreg de la tastatura
        ; scanf("%d", &n)
        push dword n
        push dword read_format
        call [scanf]
        add esp, 2*4    ; clean stack
        
        ; getch();
        call [getchar]
        
        ; afisez un mesaj
        ; printf(msg2)
        push dword msg2
        call [printf]
        add esp, 1*4
        

        ; citesc un caracter de la tastatura
        ; scanf("%c", &c1)
        push dword c1
        push dword char_format
        call [scanf]
        add esp, 2*4    ; clean stack
        
        
        ; afisez numarul citit pe ecran
        ;printf("Am citit numarul %d si litera %c", n, c1)
        xor eax, eax
        mov al, [c1]
        push eax
        push dword [n]
        push dword print_format
        call [printf]
        add esp, 2*4    ; clean stack
        
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
