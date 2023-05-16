bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s db '+', '4', '2', 'a', '8', '4', 'X', '5'
    
    ; The length of S
    l equ $ - s
    
    ; Allocate enough bytes to be sure we can write the result there
    d times l db 0

; our code starts here
segment code use32 class=code
    start:
        ; Loop l times
        mov ECX, l
        mov ESI, 0   ; Array index of S
        push dword 0 ; Array index of D
        LoopStart:
            ; AL = s[ESI]
            mov AL, [s + ESI]
            
            ; Skip to the next one if conditions are not met
            cmp AL, '0'
            jl NotDigit
            cmp AL, '9'
            jg NotDigit
            
            ; Backup ESI and copy the byte to D
            mov EDX, ESI
            pop ESI
            mov [d + ESI], AL
            inc ESI
            push ESI
            mov ESI, EDX
         
            NotDigit:
            
            inc ESI ; move forwards in the array
        loop LoopStart
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
