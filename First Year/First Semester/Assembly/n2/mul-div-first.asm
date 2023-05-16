bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 0x10
    b db 0x30
    c db 0x19
    d dw 0x3AA0

; our code starts here
segment code use32 class=code
    start:
        ; Multiplications, divisions 18) 200 - [3 * (c + b - d / a) - 300]
        ; a, b, c - byte, d - word
        
        ; BX = d / a
        mov DX, 0x0
        mov AX, [d]
        mov BL, [a]
        mov BH, 0x0
        div word BX
        mov BX, AX
        
        ; AX = c + b
        mov AH, 0x0
        mov AL, [c]
        add AL, [b]
        
        ; DX, AX = 3 * (AX - BX) - 300
        ; We shall ignore the overflow for now if it occurs, I would need to use EAX otherwise
        sub AX, BX
        mov BH, byte 0x0
        mov BL, byte 0x3
        mul BX
        sub AX, 0x12C ; 300 in hex
        
        ; AX = 200 - AX
        mov BX, AX
        mov AH, 0x0
        mov AL, byte 0xC8 ; 200 in hex
        sub AX, BX
        
        ; Final result is in AX
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
