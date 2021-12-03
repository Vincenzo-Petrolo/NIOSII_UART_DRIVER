#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "system.h"
#include "sys/alt_timestamp.h"
#include "altera_avalon_pio_regs.h"
#include "libuart.h"
#include "libfifo.h"

#define DEBUG 1
#define EVER ;;

#define BASE_ADDR 0x08001060

#define BAUDRATE 2400

/*Useful masks*/
#define RRDY_MASK 0x80
#define TRDY_MASK 0x40

/**
 * Used to let understand what the hell is happening
 * to the isr.
 */
typedef struct context
{
    uart_controller_t *cntrl;
    fifo_t *fifo;
} context_t;

#define QUEUE_SIZE 1024

void uart_isr_handler(void *ctx);
void uart_isr_read(void *ctx);
void uart_isr_write(void *ctx);

int main(void)
{
    uint16_t divisor_val = 0;
    uint32_t tmp = 0;
    uint8_t queue[QUEUE_SIZE];
    uart_controller_t controller;
    fifo_t fifo;
    context_t context = {&controller, &fifo}; //this looks so pythonic and it scares me

    /*init uart controller and fifo*/
    uart_init(&controller, BASE_ADDR);
    fifo_init(&fifo, queue, QUEUE_SIZE);

    printf("NIOSII_UART_DRIVER_project4\n\n");

    /*Compute divisor*/
    divisor_val = (alt_timestamp_freq() / BAUDRATE) - 1;
    /*Update divisor*/
    uart_set_divisor(&controller, divisor_val);

    /*Clearing all interrupts*/
    uart_set_control(&controller, 0x0, 0xFFFF);

    /*Registering handler before activating interrupts*/
    alt_ic_isr_register(0, UART_0_IRQ, uart_isr_handler, &context, NULL);

    /*Setup control register to detected IRRDY and ITRDY*/
    uart_set_control(&controller, 0x00C0, 0x0000);

#if DEBUG
    printf("divisor_val:: %d\n", divisor_val);
#endif


    for (EVER) {
        tmp++;
        /*Printing on 7segment higher 24bits*/
        IOWR_ALTERA_AVALON_PIO_DATA(NIOS_7SEG_BASE, (tmp >> 8));
    }

    return 0;
}

/*Just an interrupt multiplexer*/
void uart_isr_handler(void *ctx)
{
    /**
     * Ok now we need to know who was to fire the interrupt
     * let's check it on the status register. By giving priority to read
     * because both may have generated the interrupt.
    */
    context_t *context = (context_t *) ctx;
    uint16_t status;
    uart_read_status(context->cntrl, &status);

    if ( (status & RRDY_MASK) == RRDY_MASK) {
        /*Ok, read*/
        uart_isr_read(ctx);
    } else {
        /**
         * when an interrupt like this arrives, it means
         * that i can accept another char to send back.
        */
        uart_isr_write(ctx);
    }

    return;
}


void uart_isr_read(void *ctx)
{
    context_t *context = (context_t *) ctx;
    uint8_t data;

    /*This shouldn't wait, bc interrupts signals 
    that i have data on rxdata => non blocking*/
    uart_read_rxdata(context->cntrl, &data);

    /*To implement producer consumer i add the read data to a fifo queue*/
    fifo_push(context->fifo, data);

    /*Maybe force uart_isr_write to execute?*/

    return;
}

void uart_isr_write(void *ctx)
{
    context_t *context = (context_t *) ctx;
    uint8_t data;

    if (fifo_is_empty(context->fifo)) {
        /**
         * I have nothing to transmit even if you are ready,
         * sorry to disappoint you controller :(*/
        return;
    }

    /*Pop from queue*/
    fifo_pop(context->fifo, &data);

    /*Send over uart*/
    uart_set_txdata(context->cntrl, data);

    return;
}
