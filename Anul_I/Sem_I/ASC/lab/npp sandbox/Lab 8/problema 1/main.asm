bits 32

global start

extern get_hex_digits
extern exit, printf
import exit msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
    a dd 1A2B3C4Dh
    
    max_len equ 8
    cifre resb max_len + 1
    
    format db "Valoare curenta: %s", 10, 0 
    
;Se da un numar a reprezentat pe 32 biti fara semn. Se cere sa se afiseze reprezentarea in baza 16 a lui a, precum si rezultatul permutarilor circulare ale cifrelor sale.
segment code use32 class=code
    start:
        mov ecx, 8 

    permutation_loop:
        push ecx            
        
        mov eax, [a]        
        mov edi, cifre      
        call get_hex_digits
        
        push dword cifre
        push dword format
        call [printf]
        add esp, 4*2
        
        rol dword [a], 4
        
        pop ecx             
        loop permutation_loop
        
        
        push dword 0
        call [exit]