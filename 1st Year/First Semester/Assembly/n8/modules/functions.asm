bits 32
global printArray, readIntoArrays

extern printFormat, printf

segment data use32 class=data
    printFormat db '%d ', 0x00
    readMode db 'r', 0x00
    readFormat db '%d', 0x00
    currentNumber resd 1
    fileDescriptor resd 1

segment code use32 class=code
printArray:
    mov ecx, [esp + 8]
    mov esi, [esp + 4]
    cmp ecx, 0x00
    je printArray_end
printArray_loop:
    push ecx
    push dword [esi + 4 * ecx - 4]
    push printFormat
    call [printf]
    add esp, 4 * 2
    pop ecx
    loop printArray_loop
printArray_end:
    ret

extern fopen, fclose, fscanf

readIntoArrays:
    push readMode               ;
    push dword [esp + 24]       ;
    call [fopen]                ;
    add esp, 4 * 2              ;
    mov [fileDescriptor], eax   ;   fileDescriptor = fopen(fileName, readMode)

readIntoArrays_readLoop:
    push dword currentNumber    ;
    push dword readFormat       ;
    push dword [fileDescriptor] ;
    call [fscanf]               ;
    add esp, 4 * 3              ;   fscanf

    cmp eax, -1                 ;
    je readIntoArrays_afterLoop ; -1 stops it.

    mov eax, [currentNumber]

    cmp eax, 0x00
    jl readIntoArrays_negative
    mov edx, [esp + 8]
    inc dword [edx]
    mov edx, [edx]
    mov edi, [esp + 4]
    mov [edi + edx * 4 - 4], eax 
    jmp readIntoArrays_end      ;   positive number
    readIntoArrays_negative:
    mov edx, [esp + 16]
    inc dword [edx]
    mov edx, [edx]
    mov edi, [esp + 12]
    mov [edi + edx * 4 - 4], eax 
    readIntoArrays_end:         ;   negative number

    jmp readIntoArrays_readLoop

readIntoArrays_afterLoop:
    push dword [fileDescriptor] ;
    call [fclose]               ;   fclose(fileDescriptor)
    add esp, 4 * 1
    ret