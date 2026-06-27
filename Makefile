.PHONY: all clean

sim: sim.c
	$(CC) -Wall -O0 -o sim sim.c

sim.c: src/LICENSE src/defs.h src/prototypes.h src/*.c
	cat src/LICENSE src/defs.h src/prototypes.h src/*.c > sim.c

src/prototypes.h: src/*.c
	make -C src prototypes.h

selftest.s: test/*
	cat test/intro test/test* test/outro > selftest.s

all:
	make sim
	make selftest.s

clean:
	make -C tools clean
	rm -f sim src/sim
