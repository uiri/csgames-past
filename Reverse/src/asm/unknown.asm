unknown:
    push ebp
    mov ebp, esp
    xor eax, eax
    mov ecx, 0xffffffff
    mov edi, [ebp+0x8]
    repne scasb
    not ecx
    mov edx, ecx
    shr ecx, 0x2
    mov edi, [ebp+0x4]
    mov esi, [ebp+0x8]
    rep movsd
    mov ecx, edx
    and ecx, 0x3
    rep movsb
    pop ebp
    ret
