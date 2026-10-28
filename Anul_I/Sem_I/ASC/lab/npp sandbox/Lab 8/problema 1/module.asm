bits 32

global get_hex_digits

segment data use32 class=data
    hex_table db "0123456789ABCDEF"

segment code use32 class=code
    get_hex_digits:
        push ebx
        push ecx
        push edx
        push esi
        push edi

        mov ecx, 8          
        
    convert_loop:
        rol eax, 4          
        mov ebx, eax        
        and ebx, 0x0F       

        mov dl, [hex_table + ebx]
        
        
        mov [edi], dl
        inc edi
        
        loop convert_loop

        
        mov byte [edi], 0

        pop edi
        pop esi
        pop edx
        pop ecx
        pop ebx
        ret