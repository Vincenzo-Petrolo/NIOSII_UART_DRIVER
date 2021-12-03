#ifndef __LIB_FIFO__
#define __LIB_FIFO__

#include <stdint.h>

/*Resorting to static array implementation, circular buffer*/
typedef struct fifo
{
    uint8_t *queue;
    uint32_t size;
    uint32_t front;
    uint32_t bottom;
} fifo_t;


void fifo_init(fifo_t *, uint8_t *queue, uint32_t size);

void fifo_push(fifo_t *, uint8_t value);

void fifo_pop(fifo_t *, uint8_t *value);

uint8_t fifo_is_empty(fifo_t *);

uint8_t fifo_is_full(fifo_t *);


/**
 * There's no control on full capacity of fifo, bc i expect it to be extremely fast,
 * as long as we use reasonable baud rates
 * */

#endif
