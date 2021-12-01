#include <stdio.h>
#include <stdint.h>
#include <string.h>
#if 0
#include "system.h"
#include "sys/alt_timestamp.h"
#include "altera_avalon_pio_regs.h"
#endif

#define DEBUG 1
#define EVER ;;
#define PROJECT4_1

#define BASE_ADDR 0x08001060
#define RXDATA_OFFS 0
#define TXDATA_OFFS 4
#define STATUS_OFFS 8
#define CONTROL_OFFS 12
#define DIVISOR_OFFS 16

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
	int divisor_val = 0;
  int *reg_ptr = (int *)BASE_ADDR;
  int char_to_send = 83; // 'S'

		// welcome message
  printf("NIOSII_UART_DRIVER_project4\n\n");

		// DIVISOR computation for desired BAUDRATE
  divisor_val = (alt_timestamp_freq()/BAUDRATE)-1;
	#if DEBUG
		printf("divisor_val:: %d\n", divisor_val);
	#endif

  char string[] = "Ciao da FPGAlovers";

  for (size_t i = 0; i < strlen(string); i++)
  {
    uart_write_data((uint8_t) string[i]);
  }
  

	for(EVER);

	return 0;
}
#endif

void uart_set_register(uint32_t reg_addr, uint16_t value)
{
  *(uint32_t *)reg_addr = value;

  return;
}

void uart_read_register(uint32_t reg_addr,uint16_t *regdata)
{
  *regdata = reg_addr;

  return;
}

void uart_read_data(uint16_t *read)
{
  uint16_t status_reg;

  /*wait until data is not ready on register*/
  do {
    uart_read_register(BASE_ADDR+STATUS_OFFS, &status_reg);
  } while( (status_reg & RRDY_MASK) != 1);
  /*reading*/
  *read = BASE_ADDR+RXDATA_OFFS;

  return;
}

void uart_write_data(uint8_t data)
{
  uint16_t status_reg;
  /*wait until bit is set*/
  do {
    uart_read_register(BASE_ADDR+STATUS_OFFS, &status_reg);
  } while( (status_reg & TRDY_MASK) != 1);
  /*write*/
  *(uint32_t*)(BASE_ADDR+TXDATA_OFFS) = data;

  return;
}