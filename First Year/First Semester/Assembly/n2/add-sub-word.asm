bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dw 0xFFFF
    b dw 0x1111
    c dw 0x3333
    d dw 0x5555

; our code starts here
segment code use32 class=code
    start:
        ; Additions, subtractions - word 18) (a-b-c)+(a-c-d-d)
        
        ; Calculate (a-b-c) and store it in AX
        mov AX, [a]
        sub AX, [b]
        sub AX, [c]
        
        ; Calculate (a-c-d-d) and store it in BX
        mov BX, [a]
        sub BX, [c]
        sub BX, [d]
        sub BX, [d]
        
        ; Add BX to AX
        add AX, BX
        
        ; Result is stored in AX
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
