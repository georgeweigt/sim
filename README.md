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
     -l        Print a listing and exit
     -b nnnn   Set a breakpoint at hex address nnnn
     -t nnnn   Set a tracepoint at hex address nnnn
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
     lda  #foo>>8
```
Dollar sign provides the current location:
```
     beq  $+5
     jmp  foo
```
Hex constants start with dollar sign:
```
     lda  #$ff
```
