#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "system.h"
#include "sys/alt_timestamp.h"
#include "altera_avalon_pio_regs.h"
#include "libuart.h"

#define DEBUG 1
#define EVER ;;

#define PROJECT9_1

#define BASE_ADDR 0x08001060
#define RXDATA_OFFS 0
#define TXDATA_OFFS 4
#define STATUS_OFFS 8
#define CONTROL_OFFS 12
#define DIVISOR_OFFS 16

#define BAUDRATE 2400  //here modify BAUDRATE to increase/decrease DIVISOR


#define RRDY_MASK 0x80
#define PE_MASK 0x1



/**
 * Useful functions
  int alt_timestamp_freq(void)
  void alt_timestamp_start(void)
  int alt_timestamp(void)
  IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN_BASE, value);
*/


#ifdef PROJECT9_1
int main()
{
  uint16_t divisor_val;
  uint16_t arriving_char;
  uart_controller_t controller;
  uint16_t status_val;
  uint16_t PE_bit;

 	 // welcome message
  	printf("NIOSII_UART_DRIVER_project5_1\n\n");

	// DIVISOR computation for desired BAUDRATE
 	divisor_val = (alt_timestamp_freq()/BAUDRATE)-1;
 	printf("divisor_val:: %d\n", divisor_val);

	//Write divisor_val in DIVISOR register
	uart_set_divisor(&controller, divisor_val);


	//disable all interrupts
	uart_set_control(&controller, 0x0, 0xFFFF);


	for(EVER){

		//reading
		uart_read_status(&controller, &status_val);
		printf("STATUS register before reading:: %d\n", status_val);

		uart_read_rxdata(&controller, &arriving_char);
		
	#ifdef DEBUG
		IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN_BASE, 1);
		for(int i=0;i<100;i++);
		IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN_BASE, 0);
	#endif

	  	printf("Character received: %c\n ", arriving_char);

	  	uart_read_status(&controller, status_val);
		printf("STATUS register after reading:: %d\n", status_val);
		//check PE
		PE_bit=status_val & PE_MASK;
		printf("PE bit:: %d\n", PE_bit);
		if(PE_bit==1){
			printf("PARITY ERROR!!!\n");
			uart_clear_status(&controller);
		}

		divisor_val += 2;

		/*Updating dynamically the divisor by fixed amount*/
		uart_set_divisor(&controller, divisor_val);
	}

	return 0;
}
#endif

