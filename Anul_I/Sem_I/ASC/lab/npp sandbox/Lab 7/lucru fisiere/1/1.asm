bits 32 

global start        


extern exit, fopen, fclose, fread, printf               
import exit msvcrt.dll    
import fopen msvcrt.dll    
import fclose msvcrt.dll    
import fread msvcrt.dll    
import printf msvcrt.dll    


segment data use32 class=data
    nume_fisier db "ana.txt", 0
    mod_acces db "r", 0
    
    len equ 100
    text times (len+1) db 0
    descriptor_fis dd -1
    format_afisare db "Numarul de vocale este: %u", 0

    
; Se da un fisier text. Sa se citeasca continutul fisierului,
; sa se contorizeze numarul de vocale si sa se afiseze aceasta valoare.
; Numele fisierului text este definit in segmentul de date.
segment code use32 class=code
    start:
        ; EAX=fopen(nume_fisier, mod_acces)
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 2*4
        
        mov [descriptor_fis], eax
        cmp eax, 0
        je final
        
        ; EAX=fread(text, 1, len, descriptor_fis)
        push dword [descriptor_fis]
        push dword len
        push dword 1
        push dword text
        call [fread]
        add esp, 4*4
        
        cmp eax, 0
        je afisare
        
        ; rezolvarea logica a problemei
        mov esi, text
        mov ecx, eax
        cld
        
        xor ebx, ebx          ;contor vocale
        
        repeta:
            lodsb           ;al primeste un caracter
            cmp al, 'a'
            je vocala
            cmp al, 'e'
            je vocala
            cmp al, 'i'
            je vocala
            cmp al, 'o'
            je vocala
            cmp al, 'u'
            je vocala
            cmp al, 'A'
            je vocala
            cmp al, 'E'
            je vocala
            cmp al, 'I'
            je vocala
            cmp al, 'O'
            je vocala
            cmp al, 'U'
            je vocala
            jmp next
            vocala:
                inc ebx
            next:
                loop repeta
                
        afisare:
        ; printf(format_afisare, ebx)
        push ebx
        push dword format_afisare
        call [printf]
        add esp, 2*4
        
        ; fclose(descriptor_fis)
        push dword [descriptor_fis]
        call [fclose]
        add esp, 1*4
        
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
