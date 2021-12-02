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

#ifdef PROJECT4_1
#define BAUDRATE 2400
int main(void)
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

#ifdef PROJECT4_2

#define BAUDRATE 2400

#define INTERESTING_THOUGHS "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas sed velit non risus mollis fringilla. Pellentesque ac scelerisque ipsum. Fusce vehicula imperdiet pharetra. Ut tellus erat, suscipit malesuada dolor non, cursus blandit sem. Nullam bibendum nisi ut augue auctor, hendrerit interdum libero sollicitudin. Mauris felis ex, ultricies suscipit metus et, tristique imperdiet augue. Fusce gravida consectetur libero eu pharetra. Proin at egestas est.\
Cras elementum massa a lacinia ultrices. Nulla sed velit eu ex condimentum sollicitudin eu sit amet mi. Ut vestibulum vestibulum nulla, id consectetur est posuere faucibus. Suspendisse placerat dignissim turpis sit amet interdum. Nulla at vestibulum ante. Cras gravida augue vel enim aliquam congue. Praesent fermentum, elit vel dapibus luctus, mi est interdum ante, vitae tristique eros sem eget lorem. Nullam viverra, risus nec luctus suscipit, metus lorem viverra lorem, et condimentum lorem felis in magna. Phasellus dignissim tortor est, ac laoreet nisi volutpat sit amet. Phasellus porttitor orci felis, non semper lorem varius blandit. Fusce lacus elit, tincidunt sed convallis sed, mattis et tortor. Aliquam semper felis arcu, ac lobortis tellus interdum id.\
Nullam felis odio, efficitur id diam et, egestas sollicitudin nisi. Phasellus at laoreet nisi. Nullam molestie tellus vitae eros pharetra, nec tempor est consectetur. Proin lacinia feugiat justo ut sagittis. Donec non posuere velit. Integer sodales porttitor interdum. Integer eu felis non turpis viverra commodo quis id neque. Integer accumsan vel lacus vitae pellentesque. Vivamus a accumsan enim. Sed eleifend purus lectus. Sed vitae nulla ultrices, ultricies mauris a, finibus metus. Phasellus congue eleifend fermentum. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Aliquam rhoncus felis tincidunt ante blandit porta.\
Donec orci erat, condimentum ut nibh a, elementum vehicula ante. Cras semper ex lacus, et commodo integer."

int main(void)
{
	uint16_t divisor_val = 0;
  uint8_t string[] = INTERESTING_THOUGHS;
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