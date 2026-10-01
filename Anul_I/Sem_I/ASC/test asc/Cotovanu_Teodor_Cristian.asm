bits 32 

global start        

extern exit, scanf, printf, fopen, fclose, fprintf, getchar             
import exit msvcrt.dll    
import scanf msvcrt.dll    
import printf msvcrt.dll    
import fopen msvcrt.dll    
import fclose msvcrt.dll    
import fprintf msvcrt.dll    
import getchar msvcrt.dll    


segment data use32 class=data
    nume_fisier db "out.txt", 0
    mod_acces db "w", 0
    descriptor_fisier dd -1
    format_citireN db "%d", 0
    format_citireL db "%c", 0
    format_citireC db "%s", 0
    format_afisare db "%s ", 0
    msgN db "N: ", 0
    msgL db "L: ", 0
    msgC db "Cuvant: ", 0
    N dd 0
    L dd 0
    C times 100 db 0
    


;citeste de la tastatura, in mod repetat, un nr natural N, o litera L si un cuvant.
;programul va scrie in fisierul text indicat mai jos doar cuvintele care contin litera L si sunt formate din exact N litere.
;citirea se incheie pentru N = 0
segment code use32 class=code
    start:
        ;fopen(nume_fisier, mod_acces)
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 4*2
        
        mov [descriptor_fisier], eax
        cmp eax, 0
        je final
        
        
        repeta:
            ;printf(msgN)
            push dword msgN
            call [printf]
            add esp, 4
            
            ;scanf(format_citireN, N)       ; luam N
            push dword N
            push dword format_citireN
            call [scanf]
            add esp, 4*2
            
            call [getchar]
            
            mov eax, [N]
            cmp eax, 0                      ; iesim imediat ce N = 0
            je final_repeta
            
            ;printf(msgL)
            push dword msgL
            call [printf]
            add esp, 4
            
            ;scanf(format_citireN, L)       ; luam L
            push dword L
            push dword format_citireL
            call [scanf]
            add esp, 4*2
            
            call [getchar]
            
            ;printf(msgC)                   
            push dword msgC
            call [printf]
            add esp, 4
            
            ;scanf(format_citireN, C)       ; luam C
            push dword C
            push dword format_citireC
            call [scanf]
            add esp, 4*2
            
            call [getchar]
            

            
            ;rezolvarea logica a problemei
            mov esi, C
            cld
            xor bx, bx                  ; ok =  0 (daca gasim litera facem 1)
            xor edx, edx                ; contor de litere
            mov ecx, [L]                ; in cl vom avea litera
            parcurgere:
                lodsb                   ; luam litere rand pe rand
                cmp al, 0               ; daca nu mai sunt litere iesim
                je parcurgere_final
                inc edx                 ; nu am iesit deci incrementam numarul de litere
                cmp al, cl              ; vedem daca am gasit litera L
                jne sari
                mov bx, 1
                sari:
            jmp parcurgere
            parcurgere_final:
            cmp edx, [N]                ; sunt N litere?
            jne next
            cmp bx, 1                   ; s-a gasit litera L?
            jne next                    ; daca nu, se sare peste printare
            
            ;fprintf([descriptor_fisier], format_afisare, C)            ; Printam cuvantul C, nicio modificare, simplu
            push dword C
            push dword format_afisare
            push dword [descriptor_fisier]
            call [fprintf]
            add esp, 3*4
            
            
            next:
            
            jmp repeta
        final_repeta:
        
        ;fclose([descriptor_fisier]) (Inchidem fisierul in cazul in care acesta a fost deschis cu succes)
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4
        
        
        final:
    
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
