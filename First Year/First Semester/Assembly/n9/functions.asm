bits 32
global _convertToByteString

segment code use32 class=code
_batoi:
    mov eax, 0b0            ; Clear EAX.
    mov edx, 0b1            ; EDX = 1
    mov ecx, [esp + 4]
_batoi_find_b_loop:
    inc ecx
    cmp [ecx], byte 'b'
    jne _batoi_find_b_loop
    mov ebx, [esp + 4]
_batoi_build_eax_loop:
    dec ecx
    cmp [ecx], byte '1'
    jne _batoi_build_eax_loop_end_if
    add eax, edx
_batoi_build_eax_loop_end_if:
    shl edx, 1
    cmp ecx, ebx
    jne _batoi_build_eax_loop
    ret

_convertToByteString:
    mov ecx, [esp + 12] ; ecx = n
    mov edi, [esp + 8]  ; edi = *result
    mov esi, [esp + 4]  ; esi = **strings
_convertToByteString_loop:
    push ecx
    push edi
    push esi

    push dword [esi + 4 * ecx - 4]
    call _batoi
    add esp, 4 * 1

    pop esi
    pop edi
    pop ecx
    mov [edi + 4 * ecx - 4], eax
    loop _convertToByteString_loop
    ret