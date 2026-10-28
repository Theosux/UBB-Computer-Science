bits 32 

global start        

extern exit, fopen, fclose, fprintf
import exit msvcrt.dll    
import fopen msvcrt.dll    
import fclose msvcrt.dll    
import fprintf msvcrt.dll    

segment data use32 class=data
    nume_fisier db "output.txt", 0
    text db "Ana are mere si pere.", 0
    ; n r ees ee
    mod_acces db "w", 0
    format_afisare db "%c", 0
    format_afisarenr db "%d", 0
    descriptor_fisier dd -1
    numar dd 0

;Se dau un nume de fisier si un text (definite in segmentul de date).
;Textul contine litere mici si spatii. Sa se inlocuiasca toate literele de pe pozitii pare cu numarul pozitiei.
;Sa se creeze un fisier cu numele dat si sa se scrie textul obtinut in fisier.
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
        
        mov esi, text
        mov edi, text
        cld
        mov bl, '0'     ; contor caracter
        xor cl, cl      ; contor numeric
        
        parse:
            mov dl, cl
            xor ecx, ecx
            mov cl, dl
            mov [numar], ecx
            xor dh, dh      ; ok = 0
            lodsb
            cmp al, 0
            je stop_parse
            mov ch, cl
            test ch, 1
            jnz sari
            mov al, bl
            mov dh, 1
            sari:
            stosb
            inc bl
            inc cl
            mov dl, al
            xor eax, eax
            mov al, dl
            
            xor ch, ch
            xor bh, bh
            push cx
            push bx
            
            cmp dh, 0
            jne nr
            
            ;fprintf([descriptor_fisier], format_afisare, al)
            push eax
            push dword format_afisare
            push dword [descriptor_fisier]
            call [fprintf]
            add esp, 3*4
            
            jmp sari2
            nr:
            ;fprintf([descriptor_fisier], format_afisare, )
            push dword [numar]
            push dword format_afisarenr
            push dword [descriptor_fisier]
            call [fprintf]
            add esp, 3*4
            
            
            sari2:
            pop cx
            pop bx
            
            jmp parse
        stop_parse:
        
        ;fclose([descriptor_fisier])
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4
        
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
