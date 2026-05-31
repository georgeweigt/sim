char *
readfile(char *filename)
{
	int fd;
	char *buf;
	off_t t;

#ifndef O_BINARY
#define O_BINARY 0
#endif

	fd = open(filename, O_RDONLY | O_BINARY);

	if (fd < 0)
		return NULL;

	t = lseek(fd, 0, SEEK_END);

	if (t < 0) {
		close(fd);
		return NULL;
	}

	if (lseek(fd, 0, SEEK_SET)) {
		close(fd);
		return NULL;
	}

	buflen = (int) t;

	buf = malloc(buflen + 1);

	if (buf == NULL) {
		close(fd);
		return NULL;
	}

	if (read(fd, buf, buflen) != buflen) {
		free(buf);
		close(fd);
		return NULL;
	}

	close(fd);

	buf[buflen] = '\0';

	return buf;
}
