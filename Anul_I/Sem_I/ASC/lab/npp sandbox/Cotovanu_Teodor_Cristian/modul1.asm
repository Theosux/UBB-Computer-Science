bits 32

global _verifica_numar

segment data public data use32

segment code public code use32
    _verifica_numar:
    ;cod de intrare
    push ebp
    mov ebp, esp
    ;
    
    mov eax, [ebp + 8]          ; nr nostru
    mov ecx, [ebp + 12]         ; nr minim de cifre
    xor edx, edx
    mov ebx, eax                ; copie
    
    ; verificam mai intai daca nr este pozitiv
    test eax, 80000000h
    jnz impar
    
    ; acum verificam, pt numerele pozitive, numarul lor de cifre
    bucla:
    
        shr eax, 4
        inc edx
        cmp eax, 0
        jne bucla
    
    cmp edx, ecx
    jb nu_are_destule_cifre
    
    ; aici ramanem cu numerele care sunt pozitive si care au destule cifre
    mov eax, ebx                ; nr nostru
    xor ebx, ebx                ; copie, aplicam masca pt ultima cifra
    xor ecx, ecx                ; suma cifrelor
    xor edx, edx
    ; urmeaza sa efectuam suma
    
    suma:
    mov ebx, eax                ; copie
    and ebx, 0000000Fh          ; ebx contine ultima cifra
    add ecx, ebx                ; adunam ultima cifra la suma (ecx)
    shr eax, 4                  ; scapam de ultima cifra
    cmp eax, 0                  
    jne suma                    ; daca nr nu e 0, continuam
    
    mov eax, ecx                ; RETURNUL
    
    ; aici e partea cu nr negative, daca am ajuns aici fara a sari, sarim la final, dam return la EAX
    jmp final
    nu_are_destule_cifre:
    impar:
    mov eax, 0                  ; daca suntem in cazul gresit dam return la 0 (in C comparam cu 0 acest caz)
    final:
    ;cod de iesire
    mov esp, ebp
    pop ebp
    ret