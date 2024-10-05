bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 0x33
    c db 0x12
    d db 0x24
    f dw 0x9696

; our code starts here
segment code use32 class=code
    start:
        ; Multiplications, divisions 18) f + (c - 2) * (3 + a) / (d - 4)
        ; a, c, d - byte, f - word
        
        ; AX = (c - 2) * (3 + a)
        mov AL, [c]
        sub AL, 0x2
        mov BL, [a]
        sub BL, 0x3
        mul BL
        
        ; AX = AX / (d - 4)
        mov BL, [d]
        sub BL, 0x4
        div BL
        
        ; AX = f + AX
        add AX, [f]
        
        ; Result is in AX
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
