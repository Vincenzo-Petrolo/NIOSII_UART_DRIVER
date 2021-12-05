#include <stdio.h>
#include "system.h"
#include "sys/alt_timestamp.h"
#include "altera_avalon_pio_regs.h"




int main()
{
	int read_val;
	int ticksPerSec = alt_timestamp_freq();	// clk frequency
	int ticks_halfSec = ticksPerSec/2;

	while (1)
	{
		alt_timestamp_start();

		IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN, 0x1);			//sets pin 0 to 1 for 0.5s
		while (alt_timestamp() < ticks_halfSec);

		IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN, 0x3); 			//shows a glitch on pin 1 when the value on pin 0 is read
		read_val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN) & 0x1;
		IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN, 0x0);

		IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, 0x0);				//sets pin 0 to 0 for 0.5s
		while (alt_timestamp() < ticksPerSec);

		IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN, 0x2);
		read_val = IORD_ALTERA_AVALON_PIO_DATA(PIO_0_BASE) & 0x1;
		IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN, 0x0);
	}

  	return 0;
}