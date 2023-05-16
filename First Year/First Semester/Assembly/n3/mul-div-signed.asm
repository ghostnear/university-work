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
    b db 0x03
    c db 0x20
    d db 0x02
    e dw 0x1020
    x dq 0x01100110

; our code starts here
segment code use32 class=code
    start:
        ; Calculate 23) (a * b - 2 * c * d) / (c - e) + x / a
        ; a, b, c, d - byte; e - word; x - qword - Signed representation
        
        ; DX = a * b - 2 * c * d and save to stack
        mov AL, [a]
        imul byte [b]
        mov DX, AX
        mov AL, 0x02
        imul byte [c]
        imul byte [d]
        sub DX, AX
        push DX
        
        ; EAX = c - e and save to stack
        mov AL, [c]
        cbw
        cwde
        sub EAX, [e]
        push EAX
        
        ; (EDX, EAX) should be our old DX and EBX should be our old EAX for the division
        ; Push the result from EAX to stack
        pop EBX
        pop AX
        cwde
        cdq
        idiv EBX
        push EAX
        
        ; EAX = [x] / [a]
        mov EBX, [x]
        mov EDX, [x + 4]
        mov AL, [a]
        cbw
        cwde
        mov ECX, EAX
        mov EAX, EBX
        mov EBX, ECX
        idiv EBX
        
        ; EDX = old EAX + new EAX
        pop EDX
        add EDX, EAX
        
        ; Result is in EDX
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
