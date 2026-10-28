bits 32
global cifra_sutelor    ; facem fct globala

segment code use32 class=code

; EAX = nr
; EAX - ret nr
cifra_sutelor:
    ; EAX / 100
    mov edx, 0          ; EDX = 0
    mov ebx, 100
    div ebx             ; EAX = cat, EDX = r

    ; EAX(cat) / 10,
    mov edx, 0          ; EDX = 0
    mov ebx, 10
    div ebx             ; (restul)EDX = Cifra sutelor

    mov eax, edx        ; Mutam rezultatul (cifra sutelor) in EAX pentru a-l returna
    ret                 ; ret