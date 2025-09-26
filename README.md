Tiny 6502 simulator with built-in assembler

<br>
Build and run
```
make
./sim hello.s
```

<br>
Run a self test
```
./sim selftest.s
```

<br>
Command line options
```
-l      Send a listing to stdout and exit
-a      Trace all
-b nnnn Set a breakpoint at hex address nnnn
-t nnnn Set a tracepoint at hex address nnnn
```

<br>
Assembler pseudo-ops
```
        org
        equ
        bss
        byte
        word
```

<br>
Assembler arithmetic operators
```
+ - * / ~ & | ^ >> <<
```

<br>
Dollar sign provides the current location
```
        beq     $+5
        jmp     foo
```

<br>
Hex constants start with dollar sign
```
        lda     #$ff
```

<br>
Octal constants start with zero
```
        lda     #0377
```

<br>
Built-in functions
```
        jsr     $fff0   ; exit sim

        lda     #"y"
        jsr     $fff1   ; write to console

        jsr     $fff2   ; write string to console
        word    str

        jsr     $fff3   ; read from console, save to memory page 2
```

<br>
Program `basic.s` is under development as a port from the original Microsoft source code.
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
