#include <stdio.h>
#include "system.h"
#include "sys/alt_timestamp.h"
#include "libuart.h"

#define BR1 115200
#define BR2 2400

#define BASE_ADDRESS 0x08001060
#define EVER ;;

int main()
{
	int divisor1 = (alt_timestamp_freq()/BR1) - 1;
	printf("%d", divisor1);
	int divisor2 = (alt_timestamp_freq()/BR2) - 1;
	int *pdiv = (int *) (BASE_ADDRESS + DIVISOR_OFFS);
	printf("%d", divisor2);
	*pdiv = divisor2;
	printf("%d", *pdiv);
	for(EVER);
	return 0;
}
