// check decimal subtract algorithm

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int
main()
{
	int i, j;
	uint32_t acc, mem, cy, x, y, h, t;
	for (cy = 0; cy < 2; cy++)
	for (i = 0; i < 100; i++)
	for (j = 0; j < 100; j++) {
		acc = (i / 10) << 4 | (i % 10);
		mem = (j / 10) << 4 | (j % 10);
		t = acc - mem - cy;

		h = (acc & 0xf) - (mem & 0xf) - cy; // lower nibble subtract
		if ((t & 0x0f) > 9 || (h & 0x10))
			t -= 6;
		if ((t & 0xf0) > 0x90 || (t & 0x100))
			t -= 0x60;

		t = 100 * (t >> 8 & 1) + 10 * (t >> 4 & 0xf) + (t & 0xf);
		if (i >= j + cy) {
			if (t != i - j - cy) {
				printf("%d %d %d %d\n", cy, i, j, t);
				exit(1);
			}
		} else {
			if (t - 200 != i - j - cy) {
				printf("%d %d %d %d\n", cy, i, j, t);
				exit(1);
			}
		}
	}
	printf("ok\n");
}
