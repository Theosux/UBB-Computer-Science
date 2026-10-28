bits 32 

global start        


extern exit, printf, scanf, fopen, fclose, fprintf               
import exit msvcrt.dll    
import printf msvcrt.dll    
import scanf msvcrt.dll    
import fopen msvcrt.dll    
import fclose msvcrt.dll    
import fprintf msvcrt.dll    


segment data use32 class=data
    msgexit db "(0 = exit)", 10, 0
    msg db "Da numere: ", 0
    nume_fisier db "palindrom.txt", 0
    mod_acces db "w", 0
    descriptor_fisier dd -1
    format_afisare db "%d ", 0
    format_citire db "%d", 0
    n dd 0
    zece dd 10

    S times 101 dd 0

;Se citesc numere de la tastatură până când se introduce numarul 0.
;Toate numerele care sunt palindrom vor fi scrise în fisierul palindrom.txt, separate prin spatiu, urmate de toate numerele care nu sunt palindrom.
;La tastatura se vor introduce cel mult 100 de numere.
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
        
        ;printf(msgexit)
        push dword msgexit
        call [printf]
        add esp, 4
        
        mov edi, S
        cld
        repeta:
            ;printf(msg)
            push dword msg
            call [printf]
            add esp, 4
            
            ;scanf(format_citire, n)
            push dword n
            push dword format_citire
            call [scanf]
            add esp, 4*2
            
            mov eax, [n]
            mov ebx, eax        ; copie
            mov ecx, eax        ; copie2
            cmp eax, 0
            je sfarsit_repeta
            xor edx, edx
            
            ; aici incepe rezolvarea logica a problemei (vedem daca n este palindrom sau nu)
            
            ;caz cifra
            div dword [zece]        ; EDX:EAX = zece
            cmp eax, 0
            je palindrom
            
            ;caz 2 cifre
            cmp eax, edx
            je palindrom
            
            cmp ecx, 99
            jb next
            ;caz 3 cifre
            ; edx contina cifra din dreapta
            ; eax contine celelalte 2
            mov ebx, edx
            xor edx, edx
            div dword [zece]
            cmp eax, ebx
            je palindrom
            next:
            ;aici vom avea numerele care nu sunt palindroame:
            mov eax, ecx
            stosd
            
            jmp sari
            palindrom:
            ;fprintf([descriptor_fisier], format_afisare, ecx)
            push ecx
            push dword format_afisare
            push dword [descriptor_fisier]
            call [fprintf]
            add esp, 4*3
            sari:
            jmp repeta
        sfarsit_repeta:
        mov eax, 0
        stosd
        
        mov esi, S
        cld
        non_palindrom_loop:
            lodsd
            cmp eax, 0
            je sfarsit_npl
            
            ;fprintf([descriptor_fisier], format_afisare, eax)
            push eax
            push dword format_afisare
            push dword [descriptor_fisier]
            call [fprintf]
            add esp, 4*3            
            
            jmp non_palindrom_loop
        sfarsit_npl:
        
        ;fclose([descriptor_fisier])
        push dword [descriptor_fisier]
        call [fclose]
        add esp, 4
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
