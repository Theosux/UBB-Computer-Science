bits 32 ; assembling for the 32 bits architecture

global start        

extern exit               
import exit msvcrt.dll    
                          

segment data use32 class=data
    S dw 1432h, 8675h, 0ADBCh
    l equ ($-S)/2
    D times l dd 0



;1432h, 8675h, 0ADBCh, ...
;01020304h,  05060708h, 0A0B0C0Dh, ... 
;Se da un sir de cuvinte. Sa se obtina din acesta un sir de dublucuvinte,
;in care fiecare dublucuvant va contine nibble-urile despachetate pe octet 
;(fiecare cifra hexa va fi precedata de un 0), aranjate crescator in interiorul dublucuvantului.
segment code use32 class=code
    start:
        mov ecx, l
        cld
        mov esi, S
        mov edi, D
        jecxz Final
        Repeta:
            XOR EAX, EAX
            XOR EBX, EBX
            XOR EDX, EDX
        
            lodsb           ; AL - primul octet
            mov BL, AL      ; BL - copie
            shr AL, 4       ; AL - primii 4 biti
            shl BL, 4
            shr BL, 4       ; BL - a doua pereche de 4 biti
            mov DL, AL      ; DL - prima pereche de 4 biti
            lodsb           ; AL - al doilea octet
            mov DH, AL      ; DH - copie
            shr AL, 4       ; AL - a treia pereche de 4 biti
            shl DH, 4
            shr DH, 4       ; DH - a patra pereche de 4 biti
            ; avem DL -  prima, BL - a doua, AL - a treia, DH - a patra 
            Sortare:
                mov BH, 0   ; BH devine 1 daca se efectueaza o schimbare deci vom mai trece prin sort o data
                cmp DL, BL
                ja inversare1
                sortare2:
                    cmp BL, AL
                    ja inversare2
                sortare3:
                    cmp AL, DH
                    ja inversare3
            jmp next
            inversare1:
                mov AH, DL
                mov DL, BL
                mov BL, AH
                mov BH, 1
                jmp sortare2
            inversare2:
                mov AH, BL
                mov BL, AL
                mov AL, AH
                mov BH, 1
                jmp sortare3
            inversare3:
                mov AH, AL
                mov AL, DH
                mov DH, AH
                mov BH, 1
            next:
            cmp BH, 1
            je Sortare
            ;altfel, sirul este sortat (DL, BL, AL, DH), continuam codul
            mov AH, AL  ;(DL, BL, AH, DH)
            mov AL, DL
            stosb
            mov AL, BL
            stosb
            mov AL, AH
            stosb
            mov AL, DH
            stosb
            loop Repeta
        Final:
    
    
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
