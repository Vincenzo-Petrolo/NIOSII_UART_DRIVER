#include <stdio.h>
#include "system.h"
#include "sys/alt_timestamp.h"
#include "uartlib.h"

#DEFINE BR1 115200
#DEFINE BR2 2400

int main()
{
	int freq = alt_timestamp_freq(void);
	int divisor1 = (alt_timestamp_freq(void)/BR1) - 1;
	int divisor2 = (alt_timestamp_freq(void)/BR2) - 1;
	int *pdiv = (int *) DIVISOR;
	*pdiv = divisor2;
	printf("%d", *pdiv);
	for(EVER);
	return 0;
}