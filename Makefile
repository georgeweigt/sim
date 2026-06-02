.PHONY: all

sim: sim.c
	$(CC) -Wall -O0 -o sim sim.c

sim.c: src/LICENSE src/defs.h src/prototypes.h src/*.c
	cat src/LICENSE src/defs.h src/prototypes.h src/*.c > sim.c

selftest.s: test/*
	cat test/intro test/test* test/outro > selftest.s

all:
	make selftest.s
	make -C src
	make sim
