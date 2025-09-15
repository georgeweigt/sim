.PHONY: check clean

sim: defs.h prototypes.h *.c
	$(CC) -o sim -include defs.h -include prototypes.h *.c

prototypes.h: *.c
	make -s -C tools make-prototypes
	tools/make-prototypes *.c > prototypes.h

check:
	make -s -C tools wcheck
	tools/wcheck *.c

clean:
	rm -f sim prototypes.h
