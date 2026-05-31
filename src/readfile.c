int
readfile(char *filename)
{
	int fd;
	off_t t;

	fd = open(filename, O_RDONLY);

	if (fd < 0)
		return -1;

	t = lseek(fd, 0, SEEK_END);

	if (t < 0) {
		close(fd);
		return -1;
	}

	if (lseek(fd, 0, SEEK_SET)) {
		close(fd);
		return -1;
	}

	buflen = (int) t;

	buf = malloc(buflen + 1);

	if (buf == NULL) {
		close(fd);
		return -1;
	}

	if (read(fd, buf, buflen) != buflen) {
		free(buf);
		close(fd);
		return -1;
	}

	close(fd);

	buf[buflen] = '\0';

	return 0;
}
