bits 32
global start

;
;   18) Read from file numbers.txt a string of numbers (positive and negative). Build two strings using read(en??) numbers:
;   P – only with positive numbers.
;   N – only with negative numbers.
;   Display the strings on the screen.
;

import fopen msvcrt.dll
import fscanf msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
import exit msvcrt.dll
extern fopen, fclose, printf, exit, fscanf

%include "functions.asm"

segment data use32 class=data
    filename db 'numbers.txt', 0x00

    printPositive db 'The positive numbers are: ', 0x00
    printNegative db 'The negative numbers are: ', 0x00
    newLine db 0xA, 0xD, 0x00
    printFormat db '%d ', 0x00

    readMode db 'r', 0x00
    readFormat db '%d', 0x00
    currentNumber resd 1
    fileDescriptor resd 1

    lengthP dd 0x00
    P times 100 dd 0x00
    lengthN dd 0x00
    N times 100 dd 0x00

segment code use32 class=code
start:
    push filename               ;
    push lengthP                ;
    push P                      ;
    push lengthN                ;
    push N                      ;
    call readIntoArrays         ;
    add esp, 4 * 5              ; readIntoArrays(N, &lengthN, P, &lengthP, filename)

    push printPositive          ;
    call [printf]               ;
    add esp, 4 * 1              ; printf(printPositive)

    push dword [lengthN]        ;
    push N                      ;
    call printArray             ;
    add esp, 4 * 2              ; printArray(N, lengthN)

    push newLine                ;
    call [printf]               ;
    add esp, 4 * 1              ; printf("\n")

    push dword printNegative    ;
    call [printf]               ;
    add esp, 4 * 1              ; printf(printNegative)

    push dword [lengthP]        ;
    push P                      ;
    call printArray             ;
    add esp, 4 * 2              ; printArray(P, lengthP)

    push dword 0                ;
    call [exit]                 ; exit(0)