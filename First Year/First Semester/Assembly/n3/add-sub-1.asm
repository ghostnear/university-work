bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 0xAA
    b dw 0xAA00
    c dd 0xAA000000
    d dq 0x0100000000000000

; our code starts here
segment code use32 class=code
    start:
        ; Calculate 23) ((a + a) + (b + b) + (c + c)) - d where
        ; a - byte, b - word, c - double word, d - qword - Unsigned representation
        
        ; BX = (a + a) on words, push result to stack
        movzx AX, [a]
        mov BX, AX
        add BX, AX
        push BX
        
        ; EAX = (b + b) on double words, push result to stack
        movzx EAX, word [b]
        mov EBX, EAX
        add EAX, EBX
        push EAX
        
        ; EBX, EAX = (c + c) on quad words
        mov EAX, [c]
        add EAX, [c]
        mov EBX, 0x0
        adc EBX, 0x0
        
        ; EBX, EAX += (b + b) from the stack
        pop ECX
        add EAX, ECX
        adc EBX, 0x0
        
        mov ECX, EAX    ; (EBX, ECX) = (EBX, EAX)
        pop AX          ;
        cwde            ;
        add ECX, EAX    ; EAX = (dword) (a + a)
        adc EBX, 0x0    ; (EBX, ECX) += EAX
        
        ; (EAX, EDX) = [d]
        mov EDX, [d]
        mov EAX, [d + 4]
        sub ECX, EDX
        sbb EBX, EAX
        
        ; Result is in (EAX, EDX)
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
