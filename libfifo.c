#include "libfifo.h"


void fifo_init(fifo_t *fifo, uint8_t *queue, uint32_t size)
{
    fifo->front = fifo->bottom = 0;
    fifo->queue = queue;
    fifo->size = size;

    return;
}

void fifo_push(fifo_t *fifo, uint8_t value)
{
    /*Bottom points to the next free location*/
    fifo->queue[fifo->bottom] = value;
    /*Modulo size operation in order to start from beginning*/
    fifo->bottom = (fifo->bottom +1) % fifo->size;

    return;
}

void fifo_pop(fifo_t *fifo, uint8_t *value)
{
    /*front points to the first in, that needs to be popped first*/
    *value = fifo->queue[fifo->front];
    /*Now the front must be updated to the next element*/
    fifo->front = (fifo->front + 1) % fifo->size;

    return;
}

uint8_t fifo_is_empty(fifo_t *fifo)
{
    if (fifo->front == fifo->bottom) {
        return 1;
    } else {
        return 0;
    }
}