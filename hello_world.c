#include <stdio.h>
#include "system.h"
#include "sys/alt_timestamp.h"
#include "altera_avalon_pio_regs.h"

#define DEBUG 1
#define PROJECT3_1

#define BASE_ADDR 0x08001060
#define RXDATA_OFFS 0
#define TXDATA_OFFS 4
#define STATUS_OFFS 8
#define CONTROL_OFFS 12
#define DIVISOR_OFFS 16

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
	int *reg_ptr = (int *)BASE_ADDR;
	int char_to_send = 83; // 'S'

	// welcome message
	printf("NIOSII_UART_DRIVER_project3\n\n");

	// DIVISOR computation for desired BAUDRATE
	divisor_val = (alt_timestamp_freq()/BAUDRATE)-1;
#if DEBUG
	printf("divisor_val:: %d\n", divisor_val);
#endif

	// writes computed divisor_val into DIVISOR peripheral register
	*(reg_ptr + DIVISOR_OFFS) = divisor_val;

	// writes char to be sent into TXDATA register
	printf("\n\n*** Printing char %c ***\n\n", (char)char_to_send);
	printf("STATUS register before tx:: %d\n", *(reg_ptr + STATUS_OFFS));
	*(reg_ptr + TXDATA_OFFS) = char_to_send;
	printf("STATUS register after tx:: %d\n", *(reg_ptr + STATUS_OFFS));

	return 0;
}
#endif
