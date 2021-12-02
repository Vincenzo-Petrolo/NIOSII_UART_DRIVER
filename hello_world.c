#include <stdio.h>
#include <stdint.h>
#include <string.h>
#if 0
#include "system.h"
#include "sys/alt_timestamp.h"
#include "altera_avalon_pio_regs.h"
#endif
#include "libuart.h"

#define DEBUG 1
#define EVER ;;
#define PROJECT4_2

#define BASE_ADDR 0x08001060

#define BAUDRATE 2400

/*Useful masks*/
#define RRDY_MASK 0x80
#define TRDY_MASK 0x40


/**
 * Useful functions
  int alt_timestamp_freq(void)
  void alt_timestamp_start(void)
  int alt_timestamp(void)
  IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN_BASE, value);
*/

#ifdef PROJECT7_1
#define BAUDRATE 2400
int main(void)
{
	uint16_t divisor_val, status_val;
	uart_controller_t controller;
	uint8_t arriving_char;
	
	/*init uart controller*/
	uart_init(&controller, BASE_ADDR);

	printf("NIOSII_UART_DRIVER_project4\n\n");
	
	/*Compute divisor*/
	divisor_val = (alt_timestamp_freq()/BAUDRATE)-1;
	/*Update divisor*/
	uart_set_divisor(&controller, divisor_val);

	#if DEBUG
		printf("divisor_val:: %d\n", divisor_val);
	#endif
	
	/*disabling all interrupts for polling*/
	uart_set_control(&controller, 0);
	
	for(EVER)
	{
		uart_read_rxdata(&controller, &arriving_char);
		printf("%c", arriving_char);
		uart_read_status(&controller, &status_val);
		if ((status_val)&0x1) == 1)
		{
			printf("parity error detected");
			uart_clear_status(&controller);
		}
	}
	return(0);
}