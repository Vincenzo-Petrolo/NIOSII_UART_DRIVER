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
#define PROJECT4_1

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

void uart_set_register(uint32_t reg_addr, uint16_t value);
void uart_read_register(uint32_t reg_addr,uint16_t *regdata);
void uart_read_data(uint16_t *read);
void uart_write_data(uint8_t data);

#ifdef PROJECT4_1
int main()
{
	uint16_t divisor_val = 0;
  uint8_t string[] = "Ciao da FPGAlovers";
  uart_controller_t controller;

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


  /*Send string over UART*/
  for (size_t i = 0; i < strlen(string); i++)
  {
    uart_set_txdata(&controller, string[i]);
  }
  

	for(EVER);

	return 0;
}
#endif