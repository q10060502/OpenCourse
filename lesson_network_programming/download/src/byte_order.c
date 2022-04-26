#include "tx.h"

void byte_order()
{
	union {
		unsigned short n;
		unsigned char c[2];
	} y;
	y.n = 0x1234;
	printf("%#x\n", y.n);
	tx_mem_dump(&y, sizeof(y));

	if (y.c[0] == 0x34) {
		printf("little endian\n");
	} else {
		printf("big endian\n");
	}
}

int main(void)
{
	byte_order();
	return 0;
}
