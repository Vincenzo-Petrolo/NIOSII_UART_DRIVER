#include "libuart.h"

void uart_read_status(uart_controller_t *cntrl, uint16_t *status)
{
    *status = readw(cntrl->base_address + STATUS_OFFS);

    return;
}

/*clear all bits that are flagged as clearable (C) */
void uart_clear_status(uart_controller_t *cntrl)
{
    *(cntrl->base_address + STATUS_OFFS) = 0;

    return;
}


void uart_read_control(uart_controller_t *cntrl, uint16_t *controller)
{
    *controller = readw(cntrl->base_address + CONTROL_OFFS);

    return;
}

/*  bitmaks1 contains a mask where each 1 means that i want that bit to be set to 1
    bitmaks0 contains a mask where each 1 means that i want that bit to be set to 0
*/
void uart_set_control(uart_controller_t *cntrl, uint16_t bitmask1, uint16_t bitmask0)
{
    uint16_t control_reg;
    uart_read_controller(cntrl, &control_reg);
    control_reg |= bitmask1;
    control_reg &= ~(bitmask0);

    return;
}

void uart_set_divisor(uart_controller_t *cntrl, uint16_t value)
{
    *(cntrl->base_address + DIVISOR_OFFS) = value; 

    return;
}


void uart_read_rxdata(uart_controller_t *cntrl, uint16_t *data)
{

    /*wait RRDY to be set to 1*/

    uint16_t status;
    do {
        uart_read_status(cntrl, &status);
    } while ((status & 0x80) == 0);

    *data = readw(cntrl->base_address + RXDATA_OFFS);

    return;
}

void uart_set_txdata(uart_controller_t *cntrl, uint16_t data)
{

    /*wait TRDY to be set to 1*/
    uint16_t status;
    do {
        uart_read_status(cntrl, &status);
    } while ((status & 0x40) == 0);

    *(cntrl->base_address + TXDATA_OFFS) = data;

    return;
}

void uart_init(uart_controller_t *cntrl,uint32_t *base_address)
{
    cntrl->base_address = base_address;

    return;
}

/*Avoid compiler optimizations using volatile*/
uint16_t readw(const volatile uint16_t *addr) { 
    return *addr; 
}