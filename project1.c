#include <stdio.h>
#include "system.h"
#include "libuart.h"

#define BASE_ADDRESS 0x08001060
#define EVER ;;

int main()
{
	int *reg = (int *) BASE_ADDRESS;
	for ( int i = 0 ; i < 5; i++)
	{
		printf ( "%d\n", *reg);
		reg++;
	}
	for(EVER);
	return 0;
}
