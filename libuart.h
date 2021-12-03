#ifndef __NIOSII_LIB_UART__
#define __NIOSII_LIB_UART__
#include <stdint.h>

#define RXDATA_OFFS 0
#define TXDATA_OFFS 1
#define STATUS_OFFS 2
#define CONTROL_OFFS 3
#define DIVISOR_OFFS 4


typedef struct uart_controller
{
    uint32_t *base_address;
} uart_controller_t;

/*initialize controller with given base address*/
void uart_init(uart_controller_t *,uint32_t *base_address);

void uart_read_rxdata(uart_controller_t *cntrl, uint16_t *data);

void uart_set_txdata(uart_controller_t *cntrl, uint16_t data);

void uart_read_status(uart_controller_t *cntrl,uint16_t *status);

void uart_clear_status(uart_controller_t *cntrl);

void uart_read_control(uart_controller_t *cntrl, uint16_t *controller);

/*  bitmaks1 contains a mask where each 1 means that i want that bit to be set to 1
    bitmaks0 contains a mask where each 1 means that i want that bit to be set to 0
*/
void uart_set_control(uart_controller_t *cntrl, uint16_t bitmask1, uint16_t bitmask0);

void uart_set_divisor(uart_controller_t *cntrl, uint16_t value);

#endif
