bits 32 ; assembling for the 32 bits architecture

global start        

extern exit               
import exit msvcrt.dll    
                          

segment data use32 class=data
    S dd 127F5678h, 0ABCDABCDh
    l equ ($-S)/4
    D times l dd 0

; Se da un sir de dublucuvinte continand date impachetate (4 octeti scrisi ca un singur dublucuvant).
;Sa se obtina un nou sir de dublucuvinte, in care fiecare dublucuvant se va obtine dupa regula:
;suma octetilor de ordin impar va forma cuvantul de ordin impar, iar suma octetilor de ordin par va forma cuvantul de ordin par.
;Octetii se considera numere cu semn, astfel ca extensiile pe cuvant se vor realiza corespunzator aritmeticii cu semn.
segment code use32 class=code
    start:
        cld
        mov esi, S
        mov edi, D
        mov ecx, l
        jecxz Final
        Repeta:
            XOR EAX, EAX
            XOR EDX, EDX
            
            lodsb
            CBW
            mov BX, AX      ; primul octet - in BX
            
            lodsb
            CBW
            mov DX, AX      ; al doilea octet - in DX
            
            lodsb           
            CBW             ; al treilea octet - in AX
            
            add AX, BX      ; formam primul cuvant - AX
            stosw           ; il stocam
            
            lodsb           
            CBW             ; al patrulea octet - AL
            
            add AX, DX      ; formam al doilea cuvant - AX            
            stosw           ; il stocam
            loop Repeta
    
        Final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
