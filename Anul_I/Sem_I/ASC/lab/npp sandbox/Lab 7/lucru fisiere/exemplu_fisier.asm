bits 32 ; assembling for the 32 bits architecture


global start        

extern exit               
import exit msvcrt.dll    


segment data use32 class=data




    ; Functiile de lucru cu fisiere
    ; fread(), fprintf(), fwrite(), fprintf(fd, "%d", n), fscanf(), fclose(fd)
segment code use32 class=code
    start:

    
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
