#include <stdio.h>
#include "system.h"
#include "sys/alt_timestamp.h"
#include "altera_avalon_pio_regs.h"

#define RXDATA 0x08001060
#define TXDATA 0x08001064
#define STATUS 0x08001068
#define CONTROL 0x0800106C
#define DIVISOR 0x08001070

/**
 * Useful functions
  int alt_timestamp_freq(void)
  void alt_timestamp_start(void)
  int alt_timestamp(void)
  IOWR_ALTERA_AVALON_PIO_DATA(NIOS_HEADER_CONN_BASE, value);
*/

int main()
{
  printf("Hello from Nios II!\n");

  return 0;
}
