#include <stdio.h>
#include "system.h"
#include "sys/alt_timestamp.h"
#include "altera_avalon_pio_regs.h"

#define PIO_1_BASE 0x80010b0

#define PROJECT4
#define TOINFINITEANDBEYOND 1

#define BAUDRATE 230400
#define NBIT 8
#define NSTOPBIT 1
#define NOPARITY 0
#define EVENPARITY 1
#define ODDPARITY 2
#define PARITY NOPARITY

#define SEC_TO_MICROSEC 1000000	// microsec/sec

int main()
{
	register int val = 0x01;
	int ticksPerSec = alt_timestamp_freq();	// clk frequency
	int bit_time = SEC_TO_MICROSEC/BAUDRATE;	// microseconds
	int half_bit_time = bit_time/2;	// microseconds
	register int nticks_bit = (ticksPerSec/SEC_TO_MICROSEC)*bit_time;
	/*Declaring all as registers to achieve performances*/
	int nticks_half_bit = 0;
	register int tmp = nticks_bit + nticks_half_bit;
	register int nticks_bit1 = nticks_half_bit + 2*nticks_bit;
	register int nticks_bit3 = nticks_half_bit + 4*nticks_bit;
	register int nticks_bit5 = nticks_half_bit + 6*nticks_bit;
	register int nticks_bit7 = nticks_half_bit + 8*nticks_bit;

	register int received_char = 0;
	//short stop_error = 0;

	printf("***Welcome to PROJECT4 iamspeed***\n\n");

	IOWR_ALTERA_AVALON_PIO_DATA(NIOS_7SEG_BASE, 0x0);
	IOWR_ALTERA_AVALON_PIO_DATA(NIOS_LEDS_BASE, 0x0);


	while(TOINFINITEANDBEYOND){
		/*idles while line is high, waits for START bit*/
		while(val == 1){
			val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
		}

		/*START bit received, check it is 0*/
		alt_timestamp_start();	// starts timer

		val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;	// ALFREDO eliminato val = val & 0x01;
		if(val == 0){
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_1_BASE, 0x1);
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_1_BASE, 0x0);
			//START bit is correct, proceed
			IOWR_ALTERA_AVALON_PIO_DATA(NIOS_LEDS_BASE, 0x0);
			received_char = 0;
			tmp = nticks_bit;

			// read bit0, tmp is calculated at beginning
			while(alt_timestamp() < tmp);		// waits for bit time
			val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) ;
			received_char = received_char | ((val<<0) & 1);
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_1_BASE, 0x1);
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_1_BASE, 0x0);

			// read bit1
			while(alt_timestamp() < nticks_bit1);		// waits for bit time
			val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE);
			received_char = received_char | ((val<<1) & 2);
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_1_BASE, 0x1);
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_1_BASE, 0x0);

			// read bit2
			tmp = nticks_bit + nticks_bit1;
			while(alt_timestamp() < tmp);		// waits for bit time
			val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) ;
			received_char = received_char | ((val<<2) & 4);
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_1_BASE, 0x1);
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_1_BASE, 0x0);


			// read bit3
			while(alt_timestamp() < nticks_bit3);		// waits for bit time
			val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) ;
			received_char = received_char | ((val<<3) & 8);
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_1_BASE, 0x1);
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_1_BASE, 0x0);

			// read bit4
			tmp = nticks_bit + nticks_bit3;
			while(alt_timestamp() < tmp);		// waits for bit time
			val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) ;
			received_char = received_char | ((val<<4) & 16);
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_1_BASE, 0x1);
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_1_BASE, 0x0);

			// read bit5
			while(alt_timestamp() < nticks_bit5);		// waits for bit time
			val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) ;
			received_char = received_char | ((val<<5) & 32);
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_1_BASE, 0x1);
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_1_BASE, 0x0);

			// read bit6
			tmp = nticks_bit + nticks_bit5;
			while(alt_timestamp() < tmp);		// waits for bit time
			val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) ;
			received_char = received_char | ((val<<6) & 64);
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_1_BASE, 0x1);
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_1_BASE, 0x0);

			// read bit7
			while(alt_timestamp() < nticks_bit7);		// waits for bit time
			val = (IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE)) ;
			received_char = received_char | ((val<<7) & 128);
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_1_BASE, 0x1);
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_1_BASE, 0x0);

			// reads STOP bit 1
			tmp = nticks_bit + nticks_bit7;
			while(alt_timestamp() < tmp);		// waits for bit time
			val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_1_BASE, 0x1);
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_1_BASE, 0x0);

			/*
			if(val != 1){
				stop_error = 1;
			} is equivalent to*/

			//if(!val){
				IOWR_ALTERA_AVALON_PIO_DATA(NIOS_7SEG_BASE, received_char);
			//} else {
			//	IOWR_ALTERA_AVALON_PIO_DATA(NIOS_7SEG_BASE, 0x0666);	// you're elegant
			//}
		}
	}

	return 0;
}
