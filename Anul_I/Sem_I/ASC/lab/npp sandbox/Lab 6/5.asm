bits 32 ; assembling for the 32 bits architecture

global start        

extern exit               
import exit msvcrt.dll    


segment data use32 class=data
S1 db 7, 33, 55, 19, 46
l1 equ $-S1
S2 db 33, 21, 7, 13, 27, 19, 55, 1, 46
l2 equ $-S2
D times l2 db 0


;pos: 1, 2, 3, 4, 5
;s1: 7, 33, 55, 19, 46
;s2: 33, 21, 7, 13, 27, 19, 55, 1, 46
;d: 2, 0, 1, 0, 0, 4, 3, 0, 5

;Se dau doua siruri de octeti s1 si s2. Sa se construiasca sirul de octeti d,
;care contine pentru fiecare octet din s2 pozitia sa in s1, sau 0 in caz contrar.

segment code use32 class=code

start:
        mov ecx, l2      
        mov esi, S2      
        mov edi, D       
        jecxz Final
        
    Parcurgere:
        lodsb            
        push ecx         
        
        
        mov bl, l1       
        mov dl, 1        
        
       
        push esi         
        mov esi, S1      

        Cautare:
            cmp al, [esi]    
            je Gasit         
            
            inc dl           
            inc esi          
            dec bl
            jnz Cautare
        
        
        mov al, 0         
        jmp Final_Store
        
    Gasit:
        mov al, dl         
        
    Final_Store:
        
        pop esi          
        pop ecx            
        
        stosb              
        
        loop Parcurgere    

Final:

push dword 0 ; push the parameter for exit onto the stack

call [exit] ; call exit to terminate the program