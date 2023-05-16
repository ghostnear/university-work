bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; Original string.
    s dw 12345, 20778, 4596
    ls equ ($ - s) / 2      ; length of words
    r times ls * 5 db 0     ; maximum of 5 digits per word -> 5x length

; our code starts here
segment code use32 class=code
    start:
        ; 21) Being given a string of words, obtain the string (of bytes) of the digits in base 10 of each word from this string.
        mov ecx, ls
        mov esi, s      ; index of first string
        mov edi, r      ; index of second string
        cld
        mainLoop:
            lodsw
            mov BX, 0
            ; Decompose the number into digits and push them on the stack.
            digitsLoop:
                mov DX, 0
                
                push BX
                mov BX, 10
                div BX ; AX = DX:AX / 10, DX = DX:AX % 10
                pop BX
                
                push DX
                inc BX
                cmp AX, 0
                jne digitsLoop
            
            ; Store all BX digits from the stack.
            storageLoop:
                pop AX
                stosb
                dec BX
                cmp BX, 0
                jne storageLoop
        loop mainLoop
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
