bits 32 

global start        


extern exit, printf, scanf               
import exit msvcrt.dll    
import printf msvcrt.dll    
import scanf msvcrt.dll    



segment data use32 class=data
    msg db "", 0
    a dd 3012345120
    b dd 3999999999
    result dq 0 
    format_afisare db "<%u> + <%u> = <%lld>", 0

;Se dau doua numere naturale a si b (a, b: dword, definite in segmentul de date).
;Sa se calculeze suma lor si sa se afiseze in urmatorul format: "<a> + <b> = <result>"
;Exemplu: "1 + 2 = 3"
;Valorile vor fi afisate in format decimal (baza 10) cu semn.
segment code use32 class=code
    start:
        xor edx, edx
        mov eax, [a]
        add eax, [b]
        adc edx, 0
        mov [result], eax
        mov [result+4], edx
        
        ;printf(format_afisare, a, b, result)
        push dword [result+4]
        push dword [result]
        push dword [b]
        push dword [a]
        push format_afisare
        call [printf]
        add esp, 5*4
        
    
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
