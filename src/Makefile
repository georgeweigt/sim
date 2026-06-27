sim: defs.h prototypes.h *.c
	$(CC) -Wall -O0 -o sim -include defs.h -include prototypes.h *.c

prototypes.h: *.c
	make -C ../tools make-prototypes
	../tools/make-prototypes *.c > prototypes.h
