bits 32 ; assembling for the 32 bits architecture

global start        

extern exit, scanf, printf               
import exit msvcrt.dll    
import printf msvcrt.dll    
import scanf msvcrt.dll    


segment data use32 class=data
    msg1 db "Da numarul de numere: ", 0
    msg2 db "Da %u numere: ", 0
    format_citire db "%u", 0
    format_afisare db "%u ",10, 0
    format_medie db "Media: %u ", 0
    
    n dd 0
    c dd 0
    doi dd 2
    D times 100 dd 0


;Se va citi de la tastatura un numar n, urmat de n numere naturale. Pentru fiecare dintre cele n numere, se cere
;sã se efectueze urmatoarele operatii:
;1. Sa se afiseze de câte ori se poate imparti numarul respectiv la 2.
;2. La final, sã se afiseze media aritmetica (partea întreaga) a raspunsurilor de la subpunctul anterior.
;Date de intrare:
;3
;123
;Date de iesire:
;1
;2
;2
;Media: 1
segment code use32 class=code
    start:
        ;printf(msg1)
        push dword msg1
        call [printf]
        add esp, 4
        
        ;scanf(format_citire, n)
        push dword n
        push dword format_citire
        call [scanf]
        add esp, 2*4

        mov edi, D
        mov ecx, [n]
        jecxz final
        repeta:
        push ecx
        
        ;printf(msg2, n)
        push dword [n]
        push dword msg2
        call [printf]
        add esp, 2*4
        
        ;scanf(format_citire, c)
        push dword c
        push dword format_citire
        call [scanf]
        add esp, 2*4
        
        mov eax, [c]        
        xor ebx, ebx        ; EBX contorul
        
        test eax, eax       
        jz salvare_rezultat

    calculeaza_putere:
        cmp eax, 0         
        je salvare_rezultat
        shr eax, 1          
        inc ebx             
        jmp calculeaza_putere

    salvare_rezultat:
        mov eax, ebx        
        stosd               
        ;loop
        pop ecx
        dec ecx
        cmp ecx, 0
        jne repeta
        
        mov ecx, [n]
        xor ebx, ebx    ; media
        mov esi, D
        
        final:
        jecxz final2
        parcurge:
        push ecx
        lodsd
        push eax
        ;printf(format_afisare, eax)  ;printare caturi
        push dword eax
        push dword format_afisare
        call [printf]
        add esp, 2*4
        pop eax
        add ebx, eax        ;adunam pt medie
        pop ecx
        loop parcurge
        
        mov eax, ebx
        xor edx, edx
        div dword [n]       ;facem media
        
        ;printf(format_medie, eax)  ;printare medie
        push dword eax
        push dword format_medie
        call [printf]
        add esp, 2*4
        final2:
    
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
