#include <stdio.h>
#include "system.h"
#include "sys/alt_timestamp.h"

#DEFINE BR1 115200
#DEFINE BR2 2400

#define RXDATA 0x08001060
#define TXDATA 0x08001064
#define STATUS 0x08001068
#define CONTROL 0x0800106C
#define DIVISOR 0x08001070

int main()
{
	int freq = alt_timestamp_freq(void);
	int divisor1 = freq/BR1 - 1;
	int divisor2 = freq/BR2 - 1;
	int *pdiv = DIVISOR;
	*pdiv = divisor2;
	printf("%d", *pdiv);
	return 0;
}