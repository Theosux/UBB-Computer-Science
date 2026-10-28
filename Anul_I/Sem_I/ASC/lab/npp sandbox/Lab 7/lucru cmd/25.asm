bits 32 

global start        


extern exit, scanf, printf           
import exit msvcrt.dll    
import scanf msvcrt.dll    
import printf msvcrt.dll    


segment data use32 class=data
    msg db "Se cer numerele:", 0
    spatiu db 10, 0
    a dd 0
    b dd 0
    c dd 0
    format_citire db "%u", 0
    format_afisare db "<%u> %c <%u>", 0

; Sa se citeasca de la tastatura doua numere a si b (in baza 10)
; şi să se determine relaţia de ordine dintre ele (a < b, a = b sau a > b).
; Afisati rezultatul în următorul format: "<a> < <b>, <a> = <b> sau <a> > <b>".
segment code use32 class=code
    start:
        mov ecx, 5
        repeta:
        
        ; printf(msg)
        push msg
        call [printf]
        add esp, 1*4
        
        ; scanf(format_citire, a)
        push a
        push format_citire
        call [scanf]
        add esp, 2*4
        
        ; printf(msg)
        push msg
        call [printf]
        add esp, 1*4
        
        ; scanf(format_citire, b)
        push b
        push format_citire
        call [scanf]
        add esp, 2*4
        
        ; rezolvarea problemei (ordonam numerele, si alegem semnul)
        mov eax, [a]
        mov ebx, [b]
        cmp eax, ebx
        je egale
        jb bmare
        ja amare
        egale:
            mov dword [c], "="
            jmp next
        bmare:
            mov dword [c], "<"
            jmp next
        amare:
            mov dword [c], ">"
            jmp next
        next:
        
        ; printf(format_afisare, a, c, b)
        push dword [b]
        push dword [c]
        push dword [a]
        push format_afisare
        call [printf]
        add esp, 4*4
        
        ; printf('\n')
        push spatiu
        call [printf]
        add esp, 1*4
        
        cmp ecx, 0
        ja repeta
    
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
