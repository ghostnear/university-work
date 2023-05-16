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
        ; Calculate 23) a + b + c + d - (a + b) where
        ; a - byte, b - word, c - double word, d - qword - Signed representation
        
        ; BX = (a + b) on words, push result to stack so we can use it later at the subtraction
        movsx AX, [a]
        mov BX, [b]
        add AX, BX
        push AX
        
        ; EAX = AX + c
        cwde
        add EAX, [c]
        
        ; (EDX, EAX) = EAX + d
        cdq
        add EAX, [d]
        adc EDX, [d + 4]
        
        ; (EDX, EAX) = (EDX, EAX) - EBX
        pop EBX
        sub EAX, EBX
        sbb EDX, 0x0
        
        ; Result is in (EDX, EAX)
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
