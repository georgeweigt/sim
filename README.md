Tiny 6502 simulator with built-in assembler

To build and run:
```
make
./sim hello.s
```
To run a self test:
```
./sim selftest.s
```
Command line options:
```
-l      Send a listing to stdout and exit
-a      Trace all
-b nnnn Set a breakpoint at hex address nnnn
-t nnnn Set a tracepoint at hex address nnnn
```
Assembler pseudo-ops:
```
        org
        equ
        bss
        byte
        word
```
Assembler arithmetic operators:
```
+ - * / ~ & | ^ >> <<
```
Right shift is used to get the high byte of something:
```
        lda     #foo>>8
```
Dollar sign provides the current location:
```
        beq     $+5
        jmp     foo
```
Hex constants start with dollar sign:
```
        lda     #$ff
```
Octal constants start with zero:
```
        lda     #0377
```
Built-in functions:
```
        jsr     $fff0   ; exit sim

        lda     #"y"
        jsr     $fff1   ; write to console

        jsr     $fff2   ; write string to console
        word    str

        jsr     $fff3   ; read from console, save to memory page 2
```
`microsoft-basic.s` is under development as a port from the original Microsoft source code.
