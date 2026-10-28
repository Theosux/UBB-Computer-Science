bits 32 ; assembling for the 32 bits architecture

global start        

extern exit               
import exit msvcrt.dll    


segment data use32 class=data
    S dd 0702090Ah, 0B0C0304h, 05060108h
    l equ ($-S)/4
    l2 equ ($-S)/2
    D times l*2 db 0

;Se da un sir de 3 dublucuvinte, fiecare dublucuvant continand 2 valori pe cuvant 
;(despachetate, deci fiecare cifra hexa e precedata de un 0).
;Sa se creeze un sir de octeti care sa contina acele valori 
;(impachetate deci pe un singur octet), ordonate crescator in memorie,
;acestea fiind considerate numere cu semn.


;sir initial:
;0702090Ah, 0B0C0304h, 05060108h

;despartit
;72h, 9Ah, 0BCh, 34h, 56h, 18h

;ordonat
;9Ah, 0BCh, 18h, 34h, 56h, 72h
segment code use32 class=code
    start:
        mov ecx, l
        mov esi, S
        mov edi, D
        jecxz Final
        Despartire:
            mov al, 0
            mov bl, 0
            lodsb
            mov bl, al
            lodsb
            shl al, 4
            add al, bl
            stosb
            mov al, 0
            mov bl, 0
            lodsb
            mov bl, al
            lodsb
            shl al, 4
            add al, bl
            stosb
        loop Despartire
        ; Sortare D cu semn:
            mov ecx, l2
            dec ecx
            jecxz Final
            loop1:
                mov esi, D
                mov DH, 0 ;flag de sortare
                mov ebx, ecx
            loop2:
                mov al, [esi]
                cmp al, [esi+1]
                jle Continua
                mov dl,[esi+1]
                mov [esi], dl
                mov [esi+1], al
                mov dh, 1
            Continua:
                inc esi
                dec ebx
                jnz loop2
                
                cmp dh, 0
                je Final
                
                dec ecx
                jnz loop1
        Final:
    
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
