#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "system.h"
#include "sys/alt_timestamp.h"
#include "altera_avalon_pio_regs.h"
#include "libuart.h"

#define EVER ;;

#define BASE_ADDR 0x08001060

#define BAUDRATE 2400

int main(void)
{
	uint16_t divisor_val, status_val;
	uart_controller_t controller;
	uint16_t arriving_char;
	
	/*init uart controller*/
	uart_init(&controller, BASE_ADDR);

	printf("NIOSII_UART_DRIVER_project7\n\n");
	
	/*Compute divisor*/
	divisor_val = (alt_timestamp_freq()/BAUDRATE)-1;
	/*Update divisor*/
	uart_set_divisor(&controller, divisor_val);

	/*disabling all interrupts for polling*/
	uart_set_control(&controller, 0x0, 0xFFFF);
	
	for(EVER)
	{
		uart_read_status(&controller, &status_val);
		printf("status: %d\n",status_val);
		uart_read_rxdata(&controller, &arriving_char);
		printf("%c\n", arriving_char);
		uart_read_status(&controller, &status_val);
		if ((status_val&0x1) == 1)
		{
			printf("parity error detected, status: %d\n",status_val);
			uart_clear_status(&controller);
		}
	}
	return(0);
}
