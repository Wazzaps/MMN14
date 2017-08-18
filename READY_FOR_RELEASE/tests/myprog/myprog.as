; This program prints Joe's favorite number and loops over fibonacci numbers
; up to the 10th

; r1 = print argument
; r2 = fib index
; r3 = fib(i-2)
; r4 = fib(i-1)
; r5 = fib(i)

MYNAME:    .string  "Joe"
MYFAVNUM:  .data    35
STR1:      .string  "'s Favorite number is: "
STR2:      .string  "fib("
STR3:      .string  ") = "
NEWLINE:   .data    12       ; ascii 12 = '\n'
MAXFIBIND: .data    11       ; Count the fibonacci up to the 10th number
                             ; (stop at 11)

           .extern  PrintString
           .extern  PrintNumber
           .entry   Main

; Print <name>'s favorite number
Main:          jsr PrintFavNum

; Print fibonacci 1 & 2
               mov #1, r2
               mov #1, r5
               jsr PrintFib
               mov #2, r2
               mov #1, r5
               jsr PrintFib

; Init fibonacci
               mov #3, r2
               mov #1, r3
               mov #1, r4


; Add (n-1)+(n-2) (r3+r4) in r5
Loop:          mov r3, r5
               add r4, r5
               jsr PrintFib

; Shift elements back (n --> n-1, etc)
               mov r4, r3
               mov r5, r4

; Increment index
               add #1, r2

; Loop, or stop when reached 10
               cmp MAXFIBIND, r2
               bne Loop

               stop


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;;;;;;;        PROCEDURES        ;;;;;;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

PrintFib:      lea STR2, r1     ; "fib("
               jsr PrintString
               mov r2, r1       ; i
               jsr PrintNumber
               lea STR3, r1     ; ") = "
               jsr PrintString
               mov r5, r1       ; fib(i)
               jsr PrintNumber
               jsr PrintNewline
               rts

PrintFavNum:   jsr PrintName
               jsr PrintStr1
               mov MYFAVNUM, r1
               jsr PrintNumber
               jsr PrintNewline
               rts

PrintNewline:  prn NEWLINE
               rts

PrintName:     lea MYNAME, r1
               jsr PrintString
               rts

PrintStr1:     lea STR1, r1
               jsr PrintString
               rts