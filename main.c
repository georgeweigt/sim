int
main(int argc, char *argv[])
{
	void (*func)(void);

	opt(argc, argv);

	if (filename == NULL)
		return 1;

	if (readfile(filename) < 0)
		return 1;

	mem = malloc(65536);

	if (mem == NULL) {
		printf("malloc kaput\n");
		return 1;
	}

	scan_file(1);
	scan_file(2);

	if (lopt)
		return 0;

	pc = start;

	printf("starting at $%04x\n", (unsigned) pc);

	for (;;) {

		if (bopt && pc == bp) {
			trace();
			break;
		}

		if (aopt || (topt && pc == tp))
			trace();

		func = ftab[mem[pc++]];
		func();
	}
}

void
trace(void)
{
	int n, v, d, z, c;

	n = (flags & N) ? 1 : 0;
	v = (flags & V) ? 1 : 0;
	d = (flags & D) ? 1 : 0;
	z = (flags & Z) ? 1 : 0;
	c = (flags & C) ? 1 : 0;

	printf("Trace: PC%04x A%02x X%02x Y%02x SP%02x N%d V%d D%d Z%d C%d\n",
		(int) pc, (int) acc, (int) x, (int) y, (int) sp, n, v, d, z, c);
}

void
opt(int argc, char *argv[])
{
	int k = 1;
	char *s;

	while (k < argc) {

		s = argv[k++];

		if (strcmp(s, "-a") == 0) {
			aopt = 1;
			continue;
		}

		if (strcmp(s, "-l") == 0) {
			lopt = 1;
			continue;
		}

		if (strcmp(s, "-b") == 0) {
			if (k == argc)
				return;
			s = argv[k++];
			sscanf(s, "%x", &bp);
			bopt = 1;
			continue;
		}

		if (strcmp(s, "-t") == 0) {
			if (k == argc)
				return;
			s = argv[k++];
			sscanf(s, "%x", &tp);
			topt = 1;
			continue;
		}

		filename = s;
	}
}
