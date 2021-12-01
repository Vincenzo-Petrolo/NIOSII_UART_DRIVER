#include <stdio.h>
#include "system.h"
#include "sys/alt_timestamp.h"
#include "altera_avalon_pio_regs.h"

#define VERBOSE 1
#define EVER ;;
#define PROJECT3_1

#define RXDATA (int *)0x08001060
#define TXDATA (int *)0x08001064
#define STATUS (int *)0x08001068
#define CONTROL (int *)0x0800106C
#define DIVISOR (int *)0x08001070

#define BAUDRATE 2400

/**
 * Useful functions
  int alt_timestamp_freq(void)
  void alt_timestamp_start(void)
  int alt_timestamp(void)
  IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN_BASE, value);
*/

#ifdef PROJECT3_1
int main()
{
	int divisor_val = 0;
	int char_to_send = 83; // 'S'

	// welcome message
	printf("NIOSII_UART_DRIVER_project3\n\n");

	// DIVISOR computation for desired BAUDRATE
	divisor_val = (alt_timestamp_freq()/BAUDRATE)-1;
#if VERBOSE
	printf("divisor_val:: %d - BAUDRATE:: %d\n", divisor_val, BAUDRATE);
#endif

	// writes computed divisor_val into DIVISOR peripheral register
	*DIVISOR = divisor_val;

	// writes char to be sent into TXDATA register
	printf("\n\n*** Transmitting char %c ***\n\n", (char)char_to_send);
	printf("STATUS register before tx:: %d\n", *STATUS);
	*TXDATA = char_to_send;
	printf("STATUS register after tx:: %d\n", *STATUS);

	for(EVER);

	return 0;
}
#endif

#ifdef PROJECT3_2
int main()
{
	int divisor_val = 0;
	int char_to_send1 = 78; // 'N'
	int char_to_send2 = 73; // 'I'

	// welcome message
	printf("NIOSII_UART_DRIVER_project3\n\n");

	// DIVISOR computation for desired BAUDRATE
	divisor_val = (alt_timestamp_freq()/BAUDRATE)-1;
#if VERBOSE
	printf("divisor_val:: %d - BAUDRATE:: %d\n", divisor_val, BAUDRATE);
#endif

	// writes computed divisor_val into DIVISOR peripheral register
	*DIVISOR = divisor_val;

	// writes chars to be sent in sequence into TXDATA register
	printf("\n\n*** Transmitting 2 chars consecutively ***\n\n");
	printf("STATUS register before 1st tx:: %d\n", *STATUS);
	*TXDATA = char_to_send1;
	*TXDATA = char_to_send2;
	printf("STATUS register after 2nd tx:: %d\n", *STATUS);

	for(EVER);

	return 0;
}
#endif

#ifdef PROJECT3_3
int main()
{
	int divisor_val = 0;
	int char_to_send1 = 78; // 'N'
	int char_to_send2 = 73; // 'I'
	int char_to_send3 = 71; // 'G'

	// welcome message
	printf("NIOSII_UART_DRIVER_project3\n\n");

	// DIVISOR computation for desired BAUDRATE
	divisor_val = (alt_timestamp_freq()/BAUDRATE)-1;
#if VERBOSE
	printf("divisor_val:: %d - BAUDRATE:: %d\n", divisor_val, BAUDRATE);
#endif

	// writes computed divisor_val into DIVISOR peripheral register
	*DIVISOR = divisor_val;

	// writes chars to be sent in sequence into TXDATA register
	printf("\n\n*** Transmitting 3 chars consecutively ***\n\n");
	printf("STATUS register before 1st tx:: %d\n", *STATUS);
	*TXDATA = char_to_send1;
	*TXDATA = char_to_send2;
	*TXDATA = char_to_send3;	// should be missing
	printf("STATUS register after 3rd tx:: %d\n", *STATUS);

	for(EVER);

	return 0;
}
#endif
