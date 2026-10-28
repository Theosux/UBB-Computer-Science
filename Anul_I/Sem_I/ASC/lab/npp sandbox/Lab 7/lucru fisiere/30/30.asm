bits 32 

global start        


extern exit, fopen, fclose, scanf, fprintf, printf            
import exit msvcrt.dll    
import fopen msvcrt.dll    
import fclose msvcrt.dll    
import scanf msvcrt.dll    
import fprintf msvcrt.dll    
import printf msvcrt.dll    



segment data use32 class=data

    S times 100 db 0
    msg db "Da cuvinte: ", 0
    format_citire db "%s", 0
    format_afisare db "%s ", 0
    nume_fisier db "output.txt", 0
    mod_acces db "w", 0
    descriptor_fisier dd -1

;Se da un nume de fisier (definit in segmentul de date).
;Sa se creeze un fisier cu numele dat,
;apoi sa se citeasca de la tastatura cuvinte pana cand se citeste de la tastatura caracterul '$'.
;Sa se scrie in fisier doar cuvintele care contin cel putin o cifra.
segment code use32 class=code
    start:
        ; fopen(nume_fisier, mod_acces)
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 2*4
        
        mov [descriptor_fisier], eax
        
        cmp eax, 0
        je final
        
        
        repeta_citire:
        
            ; printf(msg)
            push dword msg
            call [printf]
            add esp, 1*4
            
            ; scanf(format_citire, S)
            push dword S
            push dword format_citire
            call [scanf]
            add esp, 2*4
            
            mov esi, S
            xor dh, dh              ; OK = 0
            parcurgere_cuvant:
                lodsb
                cld
                cmp al, 0
                je final_parcurgere
                cmp al, '$'
                je final_citire
                
                ;comparare gasire cifra:
                cmp al, '0'
                jae pas2
                jmp sari
                pas2:
                    cmp al, '9'
                    jbe pas3
                    jmp sari
                pas3:
                    mov dh, 1
                sari:
                jmp parcurgere_cuvant
            final_parcurgere:
        
            cmp dh, 1
            jne nu
            
            ;fprintf(descriptor_fisier, format_afisare, S)
            push dword S
            push dword format_afisare
            push dword [descriptor_fisier]
            call [fprintf]
            add esp, 3*4
                        
            nu:
            
            jmp repeta_citire
        final_citire:
        
        ;fclose(descriptor_fisier)
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 1*4
        
        final:
        
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
