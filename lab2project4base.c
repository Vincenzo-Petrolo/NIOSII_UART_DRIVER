#include <stdio.h>
#include "system.h"
#include "sys/alt_timestamp.h"
#include "altera_avalon_pio_regs.h"

#define DEBUG 1
#define VERBOSE 0
#define TOINFINITEANDBEYOND 1

#define BAUDRATE 115200
#define NBIT 8
#define NSTOPBIT 1
#define NOPARITY 0
#define EVENPARITY 1
#define ODDPARITY 2
#define PARITY NOPARITY

#define SEC_TO_MICROSEC 1000000	// microsec/sec

int main()
{
	int test = 0;
	int val = 0x01;
	int ticksPerSec = alt_timestamp_freq();	// clk frequency
	int bit_time = SEC_TO_MICROSEC/BAUDRATE;	// microseconds
	int half_bit_time = bit_time/2;	// microseconds
	int nticks_bit = (ticksPerSec/SEC_TO_MICROSEC)*bit_time;			//ticks for a bit
	int nticks_half_bit = (ticksPerSec/SEC_TO_MICROSEC)*half_bit_time;
	int ntcks_bit_x[1+NBIT+1+NSTOPBIT];
	int received_char = 0;
#if PARITY != NOPARITY
	int parity_value = 0;
#endif

	printf("***Welcome to PROJECT4***\n\n");

	short stop_error = 0;
	IOWR_ALTERA_AVALON_PIO_DATA(NIOS_7SEG_BASE, 0x0);			//resets 7seg
	IOWR_ALTERA_AVALON_PIO_DATA(NIOS_LEDS_BASE, 0x0);			//resets leds

	for(int i=0; i<1+NBIT+NSTOPBIT+1; ++i){
		ntcks_bit_x[i] = i * nticks_bit;			//ticks needed for every consecutive bit
	}

	while(TOINFINITEANDBEYOND){
		// idles while line is high, waits for START bit
		while(val == 1){
			val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;
		}

		// START bit received, check it is 0
		alt_timestamp_start();	// starts timer
		val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01;		//no need of waiting
#if DEBUG
			IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN, 0x1);			//glitch on NIOS_HEADER_CONN to know when we sample
				test = 1;	// sampling
			IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN, 0x0);
#endif
		if(val == 0){
			// START bit is correct, proceed
			IOWR_ALTERA_AVALON_PIO_DATA(NIOS_LEDS_BASE, 0x0);
			received_char = 0;			//resets all variables
#if PARITY != NOPARITY
			parity_value = 0;
#endif
			stop_error = 0;

			   ///// READ BIT0 /////
			while(alt_timestamp() < ntcks_bit_x[1]);		// waits for bit time
			val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) ;
#if DEBUG
			IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN, 0x1);
			test = 1;	// sampling
			IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN, 0x0);

#endif

			received_char = received_char | ((val<<0) & 1);		//updates receved_char if the received bit is 1

#if PARITY != NOPARITY
				parity_value = parity_value ^ val;				//updates parity_value

#endif

				///// READ BIT1 /////
			while(alt_timestamp() < ntcks_bit_x[2]);		// waits for bit time
			val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE);
#if DEBUG
			IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN, 0x1);
			test = 1;// sampling
			IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN, 0x0);
#endif
			received_char = received_char | ((val<<1) & 2);

#if PARITY != NOPARITY
				parity_value = parity_value ^ val;
#endif


				///// READ BIT2 /////
			while(alt_timestamp() < ntcks_bit_x[3]);		// waits for bit time
			val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE);
#if DEBUG
			IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN, 0x1);
			test = 1;// sampling
			IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN, 0x0);
#endif

			received_char = received_char | ((val<<2) & 4);

#if PARITY != NOPARITY
				parity_value = parity_value ^ val;
#endif


				///// READ BIT3 /////
			while(alt_timestamp() < ntcks_bit_x[4]);		// waits for bit time
			val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) ;
#if DEBUG
			IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN, 0x1);
			test = 1;// sampling
			WR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN, 0x0);
#endif

			received_char = received_char | ((val<<3) & 8);

#if PARITY != NOPARITY
			parity_value = parity_value ^ val;
#endif


				///// READ BIT4 /////
			while(alt_timestamp() < ntcks_bit_x[5]);		// waits for bit time
			val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE);
#if DEBUG
			IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN, 0x1);
			test = 1;// sampling
			IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN, 0x0);
#endif

				received_char = received_char | ((val<<4) & 16);

#if PARITY != NOPARITY
				parity_value = parity_value ^ val;
#endif


				///// READ BIT5 /////
			while(alt_timestamp() < ntcks_bit_x[6]);		// waits for bit time
			val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE);
#if DEBUG
			IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN, 0x1);
			test = 1;// sampling
			IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN, 0x0);
#endif

			received_char = received_char | ((val<<5) & 32);

#if PARITY != NOPARITY
			parity_value = parity_value ^ val;
#endif


			///// READ BIT6 /////
			while(alt_timestamp() < ntcks_bit_x[7]);		// waits for bit time
			val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE);
#if DEBUG
			IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN, 0x1);
			test = 1;// sampling
			IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN, 0x0);
#endif

			received_char = received_char | ((val<<6) & 64);

#if PARITY != NOPARITY
			parity_value = parity_value ^ val;
#endif


			///// READ BIT7 /////
			while(alt_timestamp() < ntcks_bit_x[8]);		// waits for bit time
			val = IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE);
#if DEBUG
			IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN, 0x1);
			test = 1;// sampling
			IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN, 0x0);
#endif

			received_char = received_char | ((val<<7) & 128);

#if PARITY != NOPARITY
			parity_value = parity_value ^ val;
#endif


#if PARITY==EVENPARITY //EVENPARITY
			// reads parity bit
			while(alt_timestamp() < ntcks_bit_x[9]);		// waits for bit time
			val = (IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01) ;
#if DEBUG
			IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN, 0x1);
			test = 1;// sampling
			IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN, 0x0);
#endif

			if(parity_value != val){
				// LED9 is ON when EVEN parity bit check fails
				IOWR_ALTERA_AVALON_PIO_DATA(NIOS_LEDS_BASE, 0x0100);
			}

#endif

#if PARITY==ODDPARITY //ODDPARITY
			// reads parity bit
			while(alt_timestamp() < ntcks_bit_x[9]);		// waits for bit time
			val = (IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01) ;
#if DEBUG
			IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN, 0x1);
			test = 1;// sampling
			IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN, 0x0);
#endif

			if(parity_value == val){
				// LED9 is ON when ODD parity bit check fails
				IOWR_ALTERA_AVALON_PIO_DATA(NIOS_LEDS_BASE, 0x080);
			}

#endif

// checks the single STOP bit or the first of a couple

#if PARITY == NOPARITY
			while(alt_timestamp() < ntcks_bit_x[9]);		// waits for bit time
#endif
#if PARITY != NOPARITY
			while(alt_timestamp() < ntcks_bit_x[10]);		// waits for bit time
#endif

			val = (IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01) ;

#if DEBUG
			IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN, 0x1);
			test = 1;// sampling
			IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN, 0x0);
#endif

			if(val != 1){
				// LED10 is ON when STOP bit(s) check fails
				IOWR_ALTERA_AVALON_PIO_DATA(NIOS_LEDS_BASE, 0x0200);
			}

// checks second STOP bit
#if NSTOPBIT==2
			// reads STOP bit 2
#if PARITY == NOPARITY
			while(alt_timestamp() < ntcks_bit_x[10]);		// waits for bit time
#endif
#if PARITY != NOPARITY
			while(alt_timestamp() < ntcks_bit_x[11]);		// waits for bit time
#endif

			val = (IORD_ALTERA_AVALON_PIO_DATA(NIOS_UARTRX_BASE) & 0x01) ;

#if DEBUG
			IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN, 0x1);
			test = 1;// sampling
			IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN, 0x0);
#endif

			if(val != 1){
				// LED10 is ON when STOP bit(s) check fails
				IOWR_ALTERA_AVALON_PIO_DATA(NIOS_LEDS_BASE, 0x0200);
			}
#endif


			if(!stop_error){
#if VERBOSE
				printf("\nReceived: %c\n", (char)received_char);
#endif
				// displays received char HEX code onto 7seg displays
				IOWR_ALTERA_AVALON_PIO_DATA(NIOS_7SEG_BASE, (char)received_char);
			} else {
#if VERBOSE
				fprintf(stderr,"\nERROR: stop bit(s) not detected.\n");	// to remove when going FAAAAST
#endif
				// displays HEX error code onto 7seg displays
				IOWR_ALTERA_AVALON_PIO_DATA(NIOS_7SEG_BASE, 0xEEEEEE);	
			}
		}
	}

	return 0;
}
#endif

