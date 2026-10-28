bits 32 

global start        


extern exit, fopen, fclose, fprintf, fread, fscanf              
import exit msvcrt.dll    
import fopen msvcrt.dll    
import fclose msvcrt.dll    
import fprintf msvcrt.dll    
import fread msvcrt.dll    
import fscanf msvcrt.dll    


segment data use32 class=data
    nume_fisier db "numere.txt", 0
    mod_acces db "r+", 0
    descriptor_fisier dd -1
    format_afisare db " %d", 0
    format_citire db "%d", 0
    max dd 0x80000000
    nr_curent dd 0
    

;Se da un fisier text.
;Fisierul contine numere (în baza 10) separate prin spatii.
;Sa se citeasca continutul acestui fisier,
;sa se determine maximul numerelor citite si sa se scrie rezultatul la sfarsitul fisierului.
segment code use32 class=code
    start:
        ;fopen(nume_fisier, mod_acces)
        push dword mod_acces
        push dword nume_fisier
        call [fopen]
        add esp, 2*4
        
        mov [descriptor_fisier], eax
        cmp eax, 0
        je final
        
        citire_loop:
        ; fscanf(descriptor_fisier, format_citire, nr_curent)
        push dword nr_curent
        push dword format_citire
        push dword [descriptor_fisier]
        call [fscanf]
        add esp, 4*3
        
        cmp eax, 1
        jne final_citire
        
        mov eax, [nr_curent]
        cmp eax, [max]
        jng next
        
        mov [max], eax
        
        next:
        jmp citire_loop
        
        final_citire:
        
        
        ;fprintf(descriptor_fisier, format_afisare, max)
        push dword [max]
        push dword format_afisare
        push dword [descriptor_fisier]
        call [fprintf]
        add esp, 3*4
        
        ;fclose(descriptor_fisier)
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4
    
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
