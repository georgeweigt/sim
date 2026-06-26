void
scan_org(struct sym *p)
{
	int t = pass;
	pass = 2; // no undefined symbols

	scan_token();
	scan_value();

	if (p)
		p->value = value;

	curloc = value;

	pass = t;
}

void
scan_equ(struct sym *p)
{
	int t = pass;
	pass = 2; // no undefined symbols

	scan_token();
	scan_value();

	if (p)
		p->value = value;

	pass = t;
}

// define bytes

void
scan_db(void)
{
	char *s;
	do {
		scan_token();
		// if 1 char then it can be used in an arithmetic expression
		if (token == T_QUOSTR && tokenlen != 1) {
			s = tokenbuf;
			while (*s)
				emit_byte(*s++);
			scan_token();
		} else {
			scan_value();
			emit_byte(value);
		}
	} while (token == ',');
}

// define words

void
scan_dw(void)
{
	do {
		scan_token();
		scan_value();
		emit_byte(value);
		emit_byte(value >> 8);
	} while (token == ',');
}

// define storage

void
scan_ds(void)
{
	int i, n, t = pass;
	pass = 2; // no undefined symbols

	scan_token(); // skip 'ds'
	scan_value();

	if (token != ',') {
		curloc += value;
		pass = t;
		return;
	}

	n = value;

	scan_token(); // skip ','
	scan_value();

	pass = t;

	for (i = 0; i < n; i++)
		emit_byte(value);
}
