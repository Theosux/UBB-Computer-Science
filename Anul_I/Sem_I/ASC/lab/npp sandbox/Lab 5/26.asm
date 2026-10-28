bits 32 ; assembling for the 32 bits architecture


global start        


extern exit               
import exit msvcrt.dll    
                          


segment data use32 class=data
    s db 1, 4, 2, 3, 8, 4, 9, 5
    len equ $-s
    max db 0                    ;initializez maxim
    
    
    
    ;Se da un sir de octeti S. Sa se determine maximul elementelor de pe pozitiile pare si minimul elementelor de pe pozitiile impare din S.
    ;Exemplu:
    ;S: 1, 4, 2, 3, 8, 4, 9, 5
    ;max_poz_pare: 9
    ;min_poz_impare: 3
    
segment code use32 class=code
    start:
        mov ecx, len
        jecxz final
        mov esi, 0              ;index de la 0
    citeste:
    
        ;citesc element pe pozitie para
        mov al, [s+esi]
        
        ;compar cu val max curent
        cmp al, [max]
        jbe mai_mic
        
        ;mai mare:
        mov [max], al
        
    mai_mic:
        add esi, 2
        cmp esi, len
        jb citeste
        ;loop citeste
    
    final:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
