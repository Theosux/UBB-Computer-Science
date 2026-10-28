bits 32 
global start        

extern exit, scanf, printf              
import exit msvcrt.dll    
import scanf msvcrt.dll    
import printf msvcrt.dll    

segment data use32 class=data
    msg1 db "(0 = exit)", 10, 0
    msg2 db "Dati numere: ", 0
    n dd 0
    min dd 0x7FFFFFFF
    format_citire db "%d", 0
    format_afisare db "Cel mai mic numar este %d", 0
;Se citesc de la tastatura numere (in baza 10) pana cand se introduce cifra 0.
;Determinaţi şi afişaţi cel mai mic număr dintre cele citite.
segment code use32 class=code
    start:
    ;printf(msg1)
    push dword msg1
    call [printf]
    add esp, 4
    
    citire:
        ;printf(msg2)
        push dword msg2
        call [printf]
        add esp, 4
        
        ;scanf(format_citire, n)
        push dword n
        push dword format_citire
        call [scanf]
        add esp, 2*4
        
        mov ebx, [n]
        cmp ebx, 0
        je final_citire
        
        mov eax, [n]
        cmp eax, [min]
        jg sari
        mov [min], eax
        sari:
        jmp citire
    final_citire:
        ;printf(format_afisare, min)
        push dword [min]
        push dword format_afisare
        call [printf]
        add esp, 2*4
    

        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
