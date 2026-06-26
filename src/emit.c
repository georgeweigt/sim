void
emit(int opcode, int count)
{
	if (start < 0)
		start = curloc;

	emit_byte(opcode);

	if (count > 1)
		emit_byte(value);

	if (count > 2)
		emit_byte(value >> 8);
}

void
emit_byte(int byte)
{
	if (lstloc < 0)
		lstloc = curloc;

	if (pass == 1) {
		curloc++;
		return;
	}

	mem[curloc++] = byte;
}
