bits 32 

global start        

extern exit, fopen, fclose, fprintf, fread, fscanf, scanf, printf               
import exit msvcrt.dll    
import fopen msvcrt.dll    
import fclose msvcrt.dll    
import fprintf msvcrt.dll    
import fread msvcrt.dll    
import fscanf msvcrt.dll    
import printf msvcrt.dll    
import scanf msvcrt.dll    

segment data use32 class=data

    S times 100 db 0
    nume_fisier db "output.txt", 0
    c dd 0
    msg_exit db "($ = exit)",10, 0
    msg db "Da cuvinte: ", 0
    format_afisare db "%s ", 0
    format_citire db "%s", 0
    mod_acces db "w", 0
    descriptor_fisier dd -1

    
;Se da un nume de fisier (definit in segmentul de date).
;Sa se creeze un fisier cu numele dat, apoi sa se citeasca de la tastatura cuvinte pana cand se citeste de la tastatura caracterul '$'.
;Sa se scrie in fisier doar cuvintele care contin cel putin o litera mica (lowercase).
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
        
        ;printf(msg_exit)
        push dword msg_exit
        call [printf]
        add esp, 4
        
        repeta_citire:
        
            ;printf(msg)
            push dword msg
            call [printf]
            add esp, 4
            
            ;scanf(format_citire, S)
            push dword S
            push dword format_citire
            call [scanf]
            add esp, 4*2
            
            xor DH, DH          ; OK = 0
            mov esi, S
            cld
            parcurgere_cuvant:
                lodsb
                cmp al, 0
                je final_parcurgere_cuvant
                cmp al, '$'
                je final_citire
                cmp al, 'a'
                jb sari
                cmp al, 'z'
                ja sari
                mov DH, 1
                sari:
                jmp parcurgere_cuvant
            final_parcurgere_cuvant:
            cmp DH, 0
            je sari2
            ;fprintf([descriptor_fisier], format_afisare, S)
                push dword S
                push dword format_afisare
                push dword [descriptor_fisier]
                call [fprintf]
                add esp, 3*4  
            sari2:
            jmp repeta_citire
        final_citire:
        
        
        final:
        
        ;fclose([descriptor_fisier])
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
