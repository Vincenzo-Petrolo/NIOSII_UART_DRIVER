#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "system.h"
#include "sys/alt_timestamp.h"
#include "altera_avalon_pio_regs.h"
#include "libuart.h"

#define DEBUG 1

#define PROJECT5_1

#define BASE_ADDR 0x08001060
#define RXDATA_OFFS 0
#define TXDATA_OFFS 4
#define STATUS_OFFS 8
#define CONTROL_OFFS 12
#define DIVISOR_OFFS 16

#define BAUDRATE 2400

#define RRDY_MASK 0x80
#define ROE_MASK 0x8



/**
 * Useful functions
  int alt_timestamp_freq(void)
  void alt_timestamp_start(void)
  int alt_timestamp(void)
  IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN_BASE, value);
*/


#ifdef PROJECT5_1
int main()
{
  uint16_t divisor_val;
  int *reg_ptr = (int *)BASE_ADDR;
  int status_reg;
  char arriving_char;
  uart_controller_t controller;
  uint16_t status_val;

 	 // welcome message
  	printf("NIOSII_UART_DRIVER_project5_1\n\n");

	// DIVISOR computation for desired BAUDRATE
 	divisor_val = (alt_timestamp_freq()/BAUDRATE)-1;
 	printf("divisor_val:: %d\n", divisor_val);

	//Write divisor_val in DIVISOR register
	uart_set_divisor(&controller, divisor_val)


	//disable all interrupts
	uart_set_control(&controller, 0x0, 0xFFFF);


	for(EVER){

		//reading
		uart_read_status(&controller, status_val);
		printf("STATUS register before reading:: %d\n", status_val);

		uart_read_rxdata(&controller, arriving_char);
		
	#ifdef DEBUG
	  	  IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN_BASE, 1);
	  	  for(int i=0;i<100;i++);
	  	  IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN_BASE, 0);
	#endif

	  	printf("Character received: %c\n ", val_read);

	  	uart_read_status(&controller, status_val);
		printf("STATUS register before reading:: %d\n", status_val);

	}

	return 0;
}
#endif

#ifdef PROJECT5_2
int main()
{
  int divisor_val = 0;
  int *reg_ptr = (int *)BASE_ADDR;
  uint16_t val_read;

   	 // welcome message
  	printf("NIOSII_UART_DRIVER_project5_2\n\n");

	// DIVISOR computation for desired BAUDRATE
 	divisor_val = (alt_timestamp_freq()/BAUDRATE)-1;
 	printf("divisor_val:: %d\n", divisor_val);

	//Write divisor_val in DIVISOR register
	uart_set_divisor(&controller, divisor_val)


	//disable all interrupts
	uart_set_control(&controller, 0x0, 0xFFFF);


	for(EVER){

	  //reading
	 uart_read_status(&controller, status_val);
		printf("STATUS register before reading:: %d\n", status_val);
	#ifdef DEBUG
	  	  IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN_BASE, 1);
	  	  for(int i=0;i<100;i++);
	  	  IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN_BASE, 0);
	#endif
	  arriving_char = *(reg_ptr+RXDATA_OFFS);
	  printf("Character received: %c\n ", arriving_char);
	 uart_read_status(&controller, status_val);
		printf("STATUS register before reading:: %d\n", status_val);
	}

	return 0;
}
#endif

#ifdef PROJECT5_3
int main()
{
  int ticks_delay=alt_timestamp_freq()*3;
  int divisor_val = 0;
  int *reg_ptr = (int *)BASE_ADDR;
  int status_reg;
  int ROE_bit;
  int val_read;

  	 // welcome message
  	printf("NIOSII_UART_DRIVER_project5_2\n\n");

	// DIVISOR computation for desired BAUDRATE
 	divisor_val = (alt_timestamp_freq()/BAUDRATE)-1;
 	printf("divisor_val:: %d\n", divisor_val);

	//Write divisor_val in DIVISOR register
	uart_set_divisor(&controller, divisor_val)


	//disable all interrupts
	uart_set_control(&controller, 0x0, 0xFFFF);


	for(EVER){
	  uart_read_status(&controller, status_val);
		printf("STATUS register before reading:: %d\n", status_val);

		uart_read_rxdata(&controller, arriving_char);

	#ifdef DEBUG
	  	  IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN_BASE, 1);
	  	  for(int i=0;i<100;i++);
	  	  IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN_BASE, 0);
	#endif
	 	printf("Character received: %c\n ", val_read);

	  	uart_read_status(&controller, status_val);
		printf("STATUS register before reading:: %d\n", status_val);

	  //delay of a few seconds
	  alt_timestamp_start();// starts timer
	  while(alt_timestamp() < ticks_delay);
          //check ROE
          	uart_read_status(&controller, status_val);
	  ROE_bit=(status_val & ROE_MASK)>>3;
	  printf("ROE bit:: %d\n", ROE_bit);
	  if(ROE_bit==1){
	      uart_clear_status(&controller);
	  }

	 }


	return 0;
}
#endif
