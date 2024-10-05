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
    b db 0x33
    c db 0x44
    d db 0x53

; our code starts here
segment code use32 class=code
    start:
        ; Additions, subtractions - byte: 18) d-(a+b)+c
        
        ; Calculate a + b store in BL
        mov BL, [a]
        add BL, [b]
        
        ; Calculate d - BL store in AL
        mov AL, [d]
        sub AL, BL
        
        ; Add c
        add AL, [c]
        
        ; AL should have the result
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
