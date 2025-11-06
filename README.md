Tiny 6502 simulator with built-in assembler

Build and run
```
make
./sim hello.s
```

Run a self test
```
./sim selftest.s
```

Command line options
```
-l      Send a listing to stdout and exit
-a      Trace all
-b nnnn Set a breakpoint at hex address nnnn
-t nnnn Set a tracepoint at hex address nnnn
```

Assembler pseudo-ops
```
        org
        equ
        bss
        byte
        word
```

Assembler arithmetic operators
```
+ - * / ~ & | ^ >> <<
```

Dollar sign provides the current location
```
        beq     $+5
        jmp     foo
```

Hex constants start with dollar sign
```
        lda     #$ff
```

Octal constants start with zero
```
        lda     #0377
```

Built-in functions
```
        jsr     $fff0   ; exit sim

        lda     #"y"
        jsr     $fff1   ; write to console

        jsr     $fff2   ; write string to console
        word    str

        jsr     $fff3   ; read input string from console into page 2 buffer
```

`basic.s` is a modified version of the original Microsoft source code.
Press return two times to accept default settings.
```
./sim basic.s
starting at $df00

MEMORY SIZE? 
TERMINAL WIDTH? 

 56319 BYTES FREE

COPYRIGHT 1978 MICROSOFT

OK
```
