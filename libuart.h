#ifndef __NIOSII_LIB_UART__
#define __NIOSII_LIB_UART__
#include <stdint.h>

#define RXDATA_OFFS 0
#define TXDATA_OFFS 4
#define STATUS_OFFS 8
#define CONTROL_OFFS 12
#define DIVISOR_OFFS 16


typedef struct uart_controller
{
    uint32_t *base_address;
} uart_controller_t;

/*initialize controller with given base address*/
void uart_init(uart_controller_t *,uint32_t *base_address);

void uart_read_rxdata(uart_controller_t *cntrl, uint8_t *data);

void uart_set_txdata(uart_controller_t *cntrl, uint8_t data);

uint16_t uart_set_status(uart_controller_t *cntrl, uint16_t bitmask);

uint16_t uart_set_control(uart_controller_t *cntrl, uint16_t bitmask);

void uart_set_divisor(uart_controller_t *cntrl, uint16_t value);

#endif