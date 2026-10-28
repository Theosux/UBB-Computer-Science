bits 32 ; assembling for the 32 bits architecture

global start        


extern exit               
import exit msvcrt.dll    



segment data use32 class=data

;Se da un sir A de cuvinte. Construiti doua siruri de octeti  
; - B1: contine ca elemente partea superioara a cuvintelor din A
; - B2: contine ca elemente partea inferioara a cuvintelor din A
segment code use32 class=code
    start:

    
    
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
