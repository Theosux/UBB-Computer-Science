bits 32 ; assembling for the 32 bits architecture

global start        

extern exit               
import exit msvcrt.dll    
                          

segment data use32 class=data
    S db 56h, 0ABh, 32h, 19h, 0h, 20h, 0C0h, 0A3h, 0FFh
    l equ $-S

; SORTARE PE S FARA SEMN
; schimba jbe -> jle pentru cu semn
segment code use32 class=code
    start:
        mov ecx, l
        dec ecx
        mov esi, S
        cld
        jecxz final
        repeta:
            lodsb                   ; AL = primul octet
            mov bl, al              ; punem in BL
            mov edx, esi
            repeta2:
                push esi
                mov esi, edx
                lodsb               ; AL = urmatorul octet
                pop esi
                cmp bl, al          ; Compararea pt sortare
                jbe next
                mov edi, esi
                dec edi
                stosb 
                xchg al, bl
                mov edi, edx
                stosb
                next:
                    inc edx
                    cmp edx, S+l
                    jl  repeta2
                loop repeta
        final:

    
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
