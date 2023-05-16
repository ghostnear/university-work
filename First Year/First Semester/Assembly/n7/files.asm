bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fscanf, fprintf, fclose, printf
import exit msvcrt.dll
import printf msvcrt.dll
import fopen msvcrt.dll
import fscanf msvcrt.dll
import fprintf msvcrt.dll
import fclose msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; File stuff
    filename db "input.txt", 0
    accessRead db "r", 0
    accessAppend db "a", 0
    descriptor dd -1
    fnfMessage db "File could not be opened!", 0
    
    ; Number stuff
    current resd 1
    readFormat db "%d", 0
    maximum resd 1
    maximumFormat db " %d", 0

; our code starts here
segment code use32 class=code
    start:
        ; 29) A text file is given. The text file contains numbers (in base 10) separated by spaces. Read the content of the file, determine the maximum number (from the numbers that have been read) and write the result at the end of file.
    
        push dword accessRead       ;
        push dword filename         ;
        call [fopen]                ;
        add ESP, 4 * 2              ; fopen
        
        cmp EAX, 0                  ;
        je onFileError              ; Check if file is valid.
        
        mov [descriptor], EAX       ; Save file descriptor

        readLoop:
            push dword current      ;
            push dword readFormat   ;
            push dword [descriptor] ;
            call [fscanf]           ;
            add ESP, 4 * 3          ; fscanf
            
            cmp EAX, -1             ;
            je afterLoop            ; -1 stops it.
            
            mov EAX, [current]      ;
            cmp EAX, [maximum]      ;
            jl notBigger            ;
            mov [maximum], EAX      ; Calculate maximum.
        
        notBigger:
            jmp readLoop
        
    afterLoop:
        push dword [descriptor]     ;
        call [fclose]               ;
        add ESP, 4 * 1              ; fclose
        
        push dword accessAppend     ;
        push dword filename         ;
        call [fopen]                ;
        add ESP, 4 * 2              ; fopen
        
        push dword [maximum]        ;
        push dword maximumFormat    ;
        push dword [descriptor]     ;
        call [fprintf]              ;
        add ESP, 4 * 3              ; fprintf
 
        push dword [descriptor]     ;
        call [fclose]               ;
        add ESP, 4 * 1              ; fclose
        jmp programEnd 
    
    onFileError:
        push dword fnfMessage       ;
        call [printf]               ;
        add ESP, 4 * 1              ; printf
    
    programEnd:
        push dword 0                ;
        call [exit]                 ; exit(0)
