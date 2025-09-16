int
main(int argc, char *argv[])
{
	void (*func)(void);
	if (argc < 2)
		return 1;
	if (readfile(argv[1]) < 0)
		return 1;
	mem = malloc(65536);
	if (mem == NULL) {
		printf("malloc kaput\n");
		return 1;
	}
	scan_file(1);
	scan_file(2);
	pc = start;
	printf("starting at $%04x\n", (unsigned) pc);
	for (;;) {
		func = ftab[mem[pc++]];
		func();
	}
}
