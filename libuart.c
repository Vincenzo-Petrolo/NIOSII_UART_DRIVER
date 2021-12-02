#include "libuart.h"

/*You can use this also for reading by applying a 16bit mask of '1's,
    for instance uart_set_status(..., 0x0000) returns the current status register.
    Values are applied by bitwise XOR mask
*/
uint16_t uart_set_status(uart_controller_t *cntrl, uint16_t bitmask)
{
    uint16_t status_reg = *(cntrl->base_address + STATUS_OFFS);
    status_reg ^= bitmask;

    return status_reg;
}

uint16_t uart_set_control(uart_controller_t *cntrl, uint16_t bitmask)
{
    uint16_t control_reg = *(cntrl->base_address + CONTROL_OFFS);
    control_reg ^= bitmask;

    return control_reg;
}

void uart_set_divisor(uart_controller_t *cntrl, uint16_t value)
{
    *(cntrl->base_address + DIVISOR_OFFS) = value; 

    return;
}


void uart_read_rxdata(uart_controller_t *cntrl, uint8_t *data)
{

    /*wait RRDY to be set to 1*/
    while ((uart_set_status(cntrl, 0x0000) & 0x80) == 0);
    

    *data = *(cntrl->base_address + RXDATA_OFFS);

    return;
}

void uart_set_txdata(uart_controller_t *cntrl, uint8_t data)
{

    /*wait TRDY to be set to 1*/
    while ((uart_set_status(cntrl, 0x0000) & 0x40) == 0);

    *(cntrl->base_address + TXDATA_OFFS) = data;

    return;
}

void uart_init(uart_controller_t *cntrl,uint32_t *base_address)
{
    cntrl->base_address = base_address;

    return;
}