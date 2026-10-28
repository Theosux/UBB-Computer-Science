bits 32 
global start        

extern exit, fread, fopen, fclose, fprintf, scanf, printf              
import exit msvcrt.dll    
import fread msvcrt.dll    
import fopen msvcrt.dll    
import fclose msvcrt.dll    
import fprintf msvcrt.dll    
import printf msvcrt.dll    
import scanf msvcrt.dll  

segment data use32 class=data
    nume_fisier db "input.txt", 0
    mod_acces db "r", 0
    descriptor_fisier dd -1
    nume times 100 dd 0
    descriptor_fisier_output dd -1
    mod_acces_output db "w", 0
    format_citire_nume db "%s", 0
    format_afisare db "%u",10, 0
    format_afisare_v db "%c",10, 0
    S times 101 db 0
    len equ 100
    D times 27 dd 0
    max dd 0
    vocala dd 0

;Sa se defineasca in segmentul de date un sir de caractere care reprezinta denumirea unui fisier. Acesta va contine un sir de maximum 100 de caractere format din litere mici, mari, cifre si caractere speciale.
;1. Sa se citeasca continutul fisierului si sa se salveze in memorie sirul citit;
;2. Sa se determine vocala (sau vocalele) care apar de un numar maxim de ori, construind in memorie un sir de frecvente (nu se va face diferente intre literele mici si mari la calculul frecventelor);
;3. Sa se citeasca de la tastatura denumirea unui nou fisier. In acest nou fisier se va scrie pe primul rand frecventa maxima, iar pe cel de al doilea caracterul/caracterele care apar de acel numar de ori, in ordine lexicografica.
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
        
        ;fread(S, 1 , len, descriptor_fisier)
        push dword [descriptor_fisier]
        push dword len
        push dword 1
        push dword S
        call [fread]
        add esp, 4*4
        
        mov ebx, eax
       
        ;fclose([descriptor_fisier])
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4
       
        ;scanf(format_citire_nume, nume)
        push dword nume
        push dword format_citire_nume
        call [scanf]
        add esp, 4*2
        
        ;fopen(nume, mod_acces_output)
        push dword mod_acces_output
        push dword nume
        call [fopen]
        add esp, 4*2
        
        mov [descriptor_fisier_output], eax
        cmp eax, 0
        je final
        
        mov esi, S
        mov ecx, ebx
        parcurgereS:
            lodsb
            cmp al, 0
            je final_parcurgere
            cmp al, 'a'
            je a
            cmp al, 'A'
            je a
            cmp al, 'e'
            je e
            cmp al, 'E'
            je e
            cmp al, 'i'
            je i
            cmp al, 'I'
            je i
            cmp al, 'o'
            je o
            cmp al, 'O'
            je o
            cmp al, 'u'
            je u
            cmp al, 'U'
            je u
            jmp sari
            a:
                inc dword [D+("A"-"@")*4]
                mov eax, [D+("A"-"@")*4]
                cmp eax, [max]
                jna saria
                mov [max], eax
                saria:
                jmp sari
            e:
                inc dword [D+("E"-"@")*4]
                mov eax, [D+("E"-"@")*4]
                cmp eax, [max]
                jna sarie
                mov [max], eax
                sarie:
                jmp sari
            i:
                inc dword [D+("I"-"@")*4]
                mov eax, [D+("I"-"@")*4]
                cmp eax, [max]
                jna sarii
                mov [max], eax
                sarii:
                jmp sari
            o:
                inc dword [D+("O"-"@")*4]
                mov eax, [D+("O"-"@")*4]
                cmp eax, [max]
                jna sario
                mov [max], eax
                sario:
                jmp sari
            u:
                inc dword [D+("U"-"@")*4]
                mov eax, [D+("U"-"@")*4]
                cmp eax, [max]
                jna sariu
                mov [max], eax
                sariu:
                jmp sari
            sari:
            dec ecx
            cmp ecx, 0
            jne parcurgereS
        final_parcurgere:
        
        ;printam frecventa maxima
        ;fprintf([descriptor_fisier_output], format_afisare, max)
        push dword [max]
        push dword format_afisare
        push dword [descriptor_fisier_output]
        call [fprintf]
        add esp, 4*3
        
        ;printam vocalele care corespund frecventei maxime:
        ;A:
        mov eax, [D+("A"-"@")*4]
        cmp eax, [max]
        jne sariafisareA
        mov dword [vocala], "a"
        ;fprintf([descriptor_fisier_output], format_afisare_v, vocala)
        push dword [vocala]
        push dword format_afisare_v
        push dword [descriptor_fisier_output]
        call [fprintf]
        add esp, 4*3
        sariafisareA:
        
        ;E:
        mov eax, [D+("E"-"@")*4]
        cmp eax, [max]
        jne sariafisareE
        mov dword [vocala], "e"
        ;fprintf([descriptor_fisier_output], format_afisare_v, vocala)
        push dword [vocala]
        push dword format_afisare_v
        push dword [descriptor_fisier_output]
        call [fprintf]
        add esp, 4*3
        sariafisareE:
        
        ;I:
        mov eax, [D+("I"-"@")*4]
        cmp eax, [max]
        jne sariafisareI
        mov dword [vocala], "i"
        ;fprintf([descriptor_fisier_output], format_afisare_v, vocala)
        push dword [vocala]
        push dword format_afisare_v
        push dword [descriptor_fisier_output]
        call [fprintf]
        add esp, 4*3
        sariafisareI:
        
        ;O:
        mov eax, [D+("O"-"@")*4]
        cmp eax, [max]
        jne sariafisareO
        mov dword [vocala], "o"
        ;fprintf([descriptor_fisier_output], format_afisare_v, vocala)
        push dword [vocala]
        push dword format_afisare_v
        push dword [descriptor_fisier_output]
        call [fprintf]
        add esp, 4*3
        sariafisareO:
        
        ;U:
        mov eax, [D+("U"-"@")*4]
        cmp eax, [max]
        jne sariafisareU
        mov dword [vocala], "u"
        ;fprintf([descriptor_fisier_output], format_afisare_v, vocala)
        push dword [vocala]
        push dword format_afisare_v
        push dword [descriptor_fisier_output]
        call [fprintf]
        add esp, 4*3
        sariafisareU:
        
        ;fclose([descriptor_fisier_output])
        push dword [descriptor_fisier_output]
        call [fclose]
        add esp, 4
        
        final:
    
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
