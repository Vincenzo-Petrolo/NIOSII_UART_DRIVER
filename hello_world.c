#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "system.h"
#include "sys/alt_timestamp.h"
#include "altera_avalon_pio_regs.h"


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
  int divisor_val = 0;
  int *reg_ptr = (int *)BASE_ADDR;
  int status_reg;
  int val_read;

  // welcome message
  printf("NIOSII_UART_DRIVER_project5_1\n\n");

	// DIVISOR computation for desired BAUDRATE
  divisor_val = (alt_timestamp_freq()/BAUDRATE)-1;
  printf("divisor_val:: %d\n", divisor_val);

	//Write divisor_val in DIVISOR register
	*(reg_ptr + DIVISOR_OFFS) = divisor_val;


	//disable all interrupts
	*(reg_ptr + CONTROL_OFFS) = 0;


	while(1){

	  //wait until register is ready
	  do {
		  status_reg=*(reg_ptr+STATUS_OFFS);
	  } while( (status_reg & RRDY_MASK) == 0);
	  //reading
	  printf("STATUS register before reading:: %d\n", *(reg_ptr + STATUS_OFFS));
	#ifdef DEBUG
	  	  IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN_BASE, 1);
	  	  for(int i=0;i<100;i++);
	  	  IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN_BASE, 0);
	#endif
	  val_read = *(reg_ptr+RXDATA_OFFS);
	  printf("Character received: %c\n ", (char)val_read);
	  printf("STATUS register after reading:: %d\n", *(reg_ptr + STATUS_OFFS));

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
	#if DEBUG
		printf("divisor_val:: %d\n", divisor_val);
	#endif

	//Write divisor_val in DIVISOR register
	*(reg_ptr + DIVISOR_OFFS) = divisor_val;

	//disable all interrupts
	*(reg_ptr + CONTROL_OFFS) = 0;

	while(1){

	  //reading
	  printf("STATUS register before reading:: %d\n", *(reg_ptr + STATUS_OFFS));
	#ifdef DEBUG
	  	  IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN_BASE, 1);
	  	  for(int i=0;i<100;i++);
	  	  IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN_BASE, 0);
	#endif
	  val_read = *(reg_ptr+RXDATA_OFFS);
	  printf("Character received: %c\n ", (char)val_read);
	  printf("STATUS register after reading:: %d\n", *(reg_ptr + STATUS_OFFS));

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
  printf("NIOSII_UART_DRIVER_project5_3\n\n");

	// DIVISOR computation for desired BAUDRATE
  divisor_val = (alt_timestamp_freq()/BAUDRATE)-1;
  printf("divisor_val:: %d\n", divisor_val);


	//Write divisor_val in DIVISOR register
	*(reg_ptr + DIVISOR_OFFS) = divisor_val;


	//disable all interrupts
	*(reg_ptr + CONTROL_OFFS) = 0;

	while(1){
	  //wait until register is ready
	  do {
		  status_reg=*(reg_ptr+STATUS_OFFS);
	  } while( (status_reg & RRDY_MASK) == 0);
	  //reading
	  printf("STATUS register before reading:: %d\n", *(reg_ptr + STATUS_OFFS));
	#ifdef DEBUG
	  	  IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN_BASE, 1);
	  	  for(int i=0;i<100;i++);
	  	  IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN_BASE, 0);
	#endif
	  val_read = *(reg_ptr+RXDATA_OFFS);
	  printf("STATUS register after reading:: %d\n", *(reg_ptr + STATUS_OFFS));
	  printf("Character received: %c\n ", (char)val_read);
	  //delay of a few seconds
	  alt_timestamp_start();// starts timer
	  while(alt_timestamp() < ticks_delay);
          //check ROE
          status_reg=*(reg_ptr+STATUS_OFFS);
	  ROE_bit=(status_reg & ROE_MASK)>>3;
	  printf("ROE bit:: %d\n", ROE_bit);
	  if(ROE_bit==1){
	      *(reg_ptr+STATUS_OFFS)= status_reg & (~(1 << 3)); //clear ROE
	  }

	 }


	return 0;
}
#endif
