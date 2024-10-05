bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a dd 1111_1111_1111_1111_1111_1111_1111_1111b

; our code starts here
segment code use32 class=code
    start:
        ; 19) Given the doubleword A, compute the doubleword B as follows:
        ;   the bits 28-31 of B have the value 1;
        ;   the bits 24- 25 and 26-27 of B are the same as the bits 8-9 of A
        ;   the bits 20-23 of B are the invert of the bits 0-3 of A ;
        ;   the bits 16-19 of B have the value 0
        ;   the bits 0-15 of B are the same as the bits 16-31 of B.
		; has been modified because of a silly mistake
        
    ; the bits 28-31 of B have the value 1;
        mov EDX, 1111b
        mov CL, 28
        shl EDX, CL
        
    ; the bits 24- 25 and 26-27 of B are the same as the bits 8-9 of A
        
        ; AL has bits 8-9 of A
        mov EAX, [a]
        mov CL, 8
        shr EAX, CL
        and AL, 11b
        
        ; EBX stays as backup
        mov EBX, 0
        mov BL, AL
        
        ; set bits 24-25 of B to the same value as bits 8-9 in A
        mov EAX, EBX
        mov CL, 24
        shl EAX, CL
        or EDX, EAX
        
        ; set bits 26-27 of B to the same value as bits 8-9 in A
        mov EAX, EBX
        mov CL, 26
        shl EAX, CL
        or EDX, EAX
        
    ; the bits 20-23 of B are the invert of the bits 0-3 of A
        mov EAX, [a]
        not EAX
        and EAX, 111b
        mov CL, 20
        shl EAX, CL
        or EDX, EAX
        
    ; the bits 16-19 of B have the value 0
    ; because of the intiial mov instruction, these bits are already set to 0
        
    ; the bits 0-15 of B are the same as the bits 16-31 of B.
        mov EAX, EDX
        mov CL, 16
        shr EAX, CL
        and EAX, 1111_1111_1111_1111b
        or EDX, EAX
        
        ; Result is stored in register EDX
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
