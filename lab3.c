#include <stdio.h>
#include "system.h"
#include "sys/alt_timestamp.h"

#DEFINE BR1 115200
#DEFINE BR2 2400

int main()
{
	int freq = alt_timestamp_freq(void);
	int divisor1 = freq/BR1 - 1;
	int divisor2 = freq/BR2 - 1;
	int *pdiv = 0x08001070;
	*pdiv = divisor2;
	printf("%d", *pdiv);
	return 0;
}