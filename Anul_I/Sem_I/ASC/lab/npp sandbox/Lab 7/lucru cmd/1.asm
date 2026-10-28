bits 32 

global start        


extern exit, scanf, printf               
import exit msvcrt.dll    
import scanf msvcrt.dll    
import printf msvcrt.dll    


segment data use32 class=data
    msg db "Dati un numar: ", 0
    n1 dd 0
    n2 dd 0
    rezultat dq 0
    format_citire db "%u", 0
    format_afisare db "Produsul numerelor este %u", 0

;Sa se citeasca de la tastatura doua numere (in baza 10) si sa se calculeze produsul lor. Rezultatul inmultirii se va salva in memorie in variabila "rezultat" (definita in segmentul de date).
segment code use32 class=code
    start:
        ; printf(msg)
        push msg
        call [printf]
        add esp, 1*4
        
        ; scanf(format_citire, n1)
        push dword n1
        push format_citire
        call [scanf]
        add esp, 2*4
        
        ; printf(msg)
        push msg
        call [printf]
        add esp, 1*4
        
        ; scanf(format_citire, n2)
        push dword n2
        push format_citire
        call [scanf]
        add esp, 2*4
        
        
        mov eax, [n2]
        mul dword [n1]             ; EDX:EAX = n1*n2
        
        mov dword [rezultat], eax
        mov dword [rezultat+4], edx
        
        ; (aditional) afisam rezultatul
        
        ; printf(format_afisare, result)
        push dword [rezultat+4]
        push dword [rezultat]
        push format_afisare
        call [printf]
        add esp, 3*4
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
