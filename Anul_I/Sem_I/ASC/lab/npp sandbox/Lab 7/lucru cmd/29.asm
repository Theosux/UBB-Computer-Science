bits 32 
global start        


extern exit, printf, scanf               
import exit msvcrt.dll    
import scanf msvcrt.dll    
import printf msvcrt.dll    


segment data use32 class=data
    a dd 0
    m dd 0
    n dd 0
    msga db "Scrie a: ", 0
    msgm db "Scrie m: ", 0
    msgn db "Scrie n: ", 0
    format_citire db "%u", 0
    format_afisare db "Numarul obtinut este: %u", 0

;Se citesc de la tastatura trei numere a, m si n (a: word, 0 <= m, n <= 15, m > n).
;Sa se izoleze bitii de la m-n ai lui a si sa se afiseze numarul intreg reprezentat de acesti bitii in baza 10.
segment code use32 class=code
    start:
        ;printf(msga)
        push dword msga
        call [printf]
        add esp, 4
        
        ;scanf(format_citire, a)
        push dword a
        push dword format_citire
        call [scanf]
        add esp, 2*4
        
        ;printf(msgm)
        push dword msgm
        call [printf]
        add esp, 4
        
        ;scanf(format_citire, m)
        push dword m
        push dword format_citire
        call [scanf]
        add esp, 2*4        
        
        ;printf(msgn)
        push dword msgn
        call [printf]
        add esp, 4
        
        ;scanf(format_citire, n)
        push dword n
        push dword format_citire
        call [scanf]
        add esp, 2*4  

        ;rezolvarea problemei:
        ; m = 3
        ; n = 7
        ; a = xxyx xxyx xxxx xxxx
        
        mov DL, [m]
        dec DL
        mov BL, 16
        sub BL, [n]
        mov AX, [a]
        mov CL, DL
        shl AX, CL  ; DX
        shr AX, CL  ; DX
        mov CL, BL
        shr AX, CL  ; BX
        
        ; AX contine bitii izolati
        xor BX, BX
        push BX
        push AX
        pop EAX
        
        ;prinf(format_afisare, AX)
        push dword EAX
        push dword format_afisare
        call [printf]
        add esp, 2*4
        
    
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
