bits 32 ; assembling for the 32 bits architecture


global start        


extern exit               
import exit msvcrt.dll    
                          
                          

segment data use32 class=data
    s1 db 0AFh, 21h, 42h
    l1 equ $-s1
    s2 db 0F3h, 0C0h, 0BDh, 23h
    l2 equ $-s2
    D times l1+l2 db 0
    L db 0

;Se dau doua siruri de octeti. 
;Sa se parcurga cel mai scurt sir dintre cele doua siruri
;si sa se construiasca un al treilea sir care va contine cel mai mare element de acelasi rang din cele doua siruri,
;iar pana la lungimea celui mai lung sir,
;sirul al treilea se va completa alternativ cu valoarea 1 respectiv 0
segment code use32 class=code
    start:
    ;gasim l maxim
    xor al, al
    xor ah, ah
    mov al, l1
    mov ah, l2
    cmp al, ah
    ja mare
    movzx [L], ah
    jmp gasit
    mare:
    movzx [L], al
    gasit:
    
    push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
