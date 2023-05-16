bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, scanf, printf               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    n resw 1    ; hd format specified for shorts
    a resb 1    ;
    b resb 1    ; hhd format specifier for bytes
    readFormat db "%hd %hhd %hhd", 0
    printFormat db "%04X", 0

; our code starts here
segment code use32 class=code
    start:
        ; 29) Read three numbers n, a and b (n: word, 0 <= a, b <= 15, b > a) from the keyboard. Isolate the bits b-a of n and display the integer represented by those bits in base 16.
        
        push dword b            ;
        push dword a            ;
        push dword n            ;
        push dword readFormat   ;
        call [scanf]            ; scanf(..., n, a, b)
        add ESP, 4 * 4
        
        mov EDX, 0x0    ;
        mov DX, [n]     ; EDX = n
        
        mov CL, [a]     ;
        shr DX, CL      ; DX >>= a 
        
        add CL, [b]     ;
        sub CL, [a]     ;
        sub CL, [a]     ; CL = b - a
        
        mov AX, 0b1     ;
        shl AX, CL      ; AX = (1 << CL)
        
        dec AX          ; AX--
        
        and DX, AX      ; DX &= AX
        
        push dword EDX          ;
        push dword printFormat  ;
        call [printf]           ; printf(..., DX)
        add ESP, 4 * 2
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
