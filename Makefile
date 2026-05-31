.PHONY: all

sim: sim.c
	$(CC) -Wall -O0 -o sim sim.c

sim.c: src/LICENSE src/defs.h src/prototypes.h src/*.c
	cat src/LICENSE src/defs.h src/prototypes.h src/*.c > sim.c

all:
	make -C src
	make -C test
	make sim
