#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
    uint8_t *buf;
    size_t   size;
    size_t   head;
    size_t   tail;
    size_t   count;
} ring_buffer_t;

void   rb_init(ring_buffer_t *rb, uint8_t *storage, size_t size);
bool   rb_put(ring_buffer_t *rb, uint8_t byte);
bool   rb_get(ring_buffer_t *rb, uint8_t *byte);
size_t rb_count(const ring_buffer_t *rb);
bool   rb_is_empty(const ring_buffer_t *rb);
bool   rb_is_full(const ring_buffer_t *rb);
void   rb_reset(ring_buffer_t *rb);

#endif
