bits 32 

global start        


extern exit, fread, fopen, fclose, fprintf, scanf, printf, fscanf            
import exit msvcrt.dll    
import fread msvcrt.dll    
import fopen msvcrt.dll    
import fclose msvcrt.dll    
import fprintf msvcrt.dll    
import printf msvcrt.dll    
import scanf msvcrt.dll  
import fscanf msvcrt.dll  

segment data use32 class=data
    nume_fisierinput db "input.txt", 0
    descriptor_fisier_input dd -1
    descriptor_fisier_output dd -1
    ;nume_fisieroutput db "output.txt", 0
    mod_acces1 db "r", 0
    mod_acces2 db "w", 0
    format_citire db "%d %d", 0
    format_afisare db "%d", 10, 0
    format_citire_fisier db "%d", 0
    d dd 0
    S times 101 dd 0
    n1 dd 0
    n2 dd 0
    nume times 100 db 0
    format_citire_numefisier db "%s", 0

;Se defineste in segmentul de date un sir de caractere care reprezinta denumirea unui fisier text.
;Fisierul contine un sir de maximum 100 de numere din intervalul [-10^9, 10^9] care se termina cu valoarea 0 (care nu face parte din sir).
;1. Sa se citeasca continutul fisierului si sa se salveze in memorie sirul citit.
;2. Sa se parcurga sirul de numere salvat si sa se construiasca in memorie sirul sumelor partiale.
;3. Sa se citeasca de la tastatura (din terminal) denumirea unui nou fisier, urmat de perechi de numere sub forma a b pana la intalnirea perechii -1 - 1 si sa se ;calculeze suma elementelor corespunzatoare subsirului care incepe la pozitia a si se termina la pozitia b. Toate sumele calculate vor fi afisate pe cate un rand in fisierul citit din terminal.
;Exemplu
;Se defineste in segmentul de date textul "input.txt". Continutul fisierului input.txt este urmatorul:
;10 3 -2 7 -5 4 -8 20 0
;Se citeste de la tastatura fisierul cu denumirea "output.txt", apoi se citesc perechile:
;0 4
;1 3
;2 5
;-1 3
;5 7
;3 8
;-1 -1
;In fisierul output.txt se va afisa, pe fiecare linie, urmatorul continut:
;13
;8
;4
;16
segment code use32 class=code
    start:
        ;fopen(nume_fisierinput, mod_acces1)
        push dword mod_acces1
        push dword nume_fisierinput
        call [fopen]
        add esp, 4*2
        
        mov [descriptor_fisier_input], eax
        cmp eax, 0
        je final
        
        mov edi, S
        cld
        
        citire_repetata:
        ;fscanf([descriptor_fisier_input], format_citire_fisier, d)
        push dword d
        push dword format_citire_fisier
        push dword [descriptor_fisier_input]
        call [fscanf]
        add esp, 3*4
        
        mov eax, [d]
        cmp eax, 0
        je final_citire
        stosd
        jmp citire_repetata
        final_citire:
        
        ;fclose([descriptor_fisier_input])
        push dword [descriptor_fisier_input]
        call [fclose]
        add esp, 4
        
        ;scanf(format_citire_numefisier, nume)
        push dword nume
        push dword format_citire_numefisier
        call [scanf]
        add esp, 2*4
        
        ;fopen(nume, mod_acces2)
        push dword mod_acces2
        push dword nume
        call [fopen]
        add esp, 2*4
        
        mov [descriptor_fisier_output], eax
        cmp eax, 0
        je final
        
        repeta:
            ;scanf(format_citire, n1, n2)
            push dword n2
            push dword n1
            push dword format_citire
            call [scanf]
            add esp, 3*4
            
            mov ebx, [n1]
            mov edx, [n2]
            cmp ebx, -1
            jne sari
            cmp edx, -1
            je final_repeta
            sari:
            cmp ebx, -1
            jle repeta
            cmp edx, 0
            jl repeta
            mov esi, S 
            mov ecx, edx
            sub ecx, ebx    ;lungimea este ultimul index minus primul
            inc ecx
            shl ebx, 2      ;ebx * 4
            add esi, ebx    ;incepem de la primul index
            xor ebx, ebx    ;suma
            repeta_suma:
            lodsd
            add ebx, eax
            loop repeta_suma
            
            ;fprintf([descriptor_fisier_output], format_afisare, ebx)
            push dword ebx
            push format_afisare
            push dword [descriptor_fisier_output]
            call [fprintf]
            add esp, 3*4
            
            jmp repeta
            final_repeta:
        ;fclose([descriptor_fisier_output])
        push dword [descriptor_fisier_output]
        call [fclose]
        add esp, 4
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
