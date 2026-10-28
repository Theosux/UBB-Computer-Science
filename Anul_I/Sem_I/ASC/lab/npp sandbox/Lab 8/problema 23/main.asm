bits 32
global start

extern exit, printf, scanf
import exit msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll

extern cifra_sutelor

segment data use32 class=data
    
    max equ 100
    s1 times max dd 0  
    s2 times max db 0  

    msg_start db "Sirul s1:", 10, 0
    msg_prompt db "Numar: ", 0
    format_citire db "%d", 0 
    format_afisare_start db "Sirul s2: ", 0
    format_afisare_cifra db "%d ", 0

    stop equ -1                         ; oprire citire
    count dd 0                          ; contor

segment code use32 class=code
    start:
        ; citire sir:
        
        ; printf(msg_start)
        push dword msg_start
        call [printf]
        add esp, 4
        
        mov edi, s1                     ; next nr
        
    citire:
        ; verificam max
        cmp dword [count], max
        je stop_citire
        
        ; printf(msg_prompt)
        push dword msg_prompt
        call [printf]
        add esp, 4
        
        ; scanf(format, edi)
        push dword edi
        push dword format_citire
        call [scanf]
        add esp, 2*4
        
        ; verificam stop
        cmp dword [edi], stop
        je stop_citire
        
        ; inc contor, pointer
        inc dword [count]
        add edi, 4                      ; Trecem la urmatorul dublucuvant
        jmp citire

    stop_citire:
        
        ; verificare:
        cmp dword [count], 0
        je Final
        
        ; formare s2:
        ;pregatire lucru cu sir
        mov ecx, [count]    ; NR elemente
        mov esi, s1         
        mov edi, s2    
        cld

    repeta_calcul:
        lodsd              
        call cifra_sutelor  
        stosb               
        loop repeta_calcul
        
        ; afisare:
        
        ; printf(format_afisare_start)
        push dword format_afisare_start
        call [printf]
        add esp, 4
        
        mov ecx, [count]    ; resetare contor
        mov esi, s2         

    afisare:
        xor eax, eax        
        lodsb               

        push ecx            ; Salvam ECX
        
        movzx eax, al       ; pt a afisa
        
        ;printf(format_afisare_cifra, eax)
        push eax            
        push dword format_afisare_cifra
        call [printf]
        add esp, 4*2        

        pop ecx            
        loop afisare

    Final:
        push dword 0
        call [exit]