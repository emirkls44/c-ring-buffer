#include "ring_buffer.h"

void rb_init(ring_buffer_t *rb, uint8_t *storage, size_t size)
{
    rb->buf  = storage;
    rb->size = size;
    rb_reset(rb);
}

void rb_reset(ring_buffer_t *rb)
{
    rb->head  = 0;
    rb->tail  = 0;
    rb->count = 0;
}

bool rb_put(ring_buffer_t *rb, uint8_t byte)
{
    if (rb_is_full(rb)) {
        return false;
    }
    rb->buf[rb->head] = byte;
    rb->head = (rb->head + 1) % rb->size;
    rb->count++;
    return true;
}

bool rb_get(ring_buffer_t *rb, uint8_t *byte)
{
    if (rb_is_empty(rb)) {
        return false;
    }
    *byte = rb->buf[rb->tail];
    rb->tail = (rb->tail + 1) % rb->size;
    rb->count--;
    return true;
}

size_t rb_count(const ring_buffer_t *rb)
{
    return rb->count;
}

bool rb_is_empty(const ring_buffer_t *rb)
{
    return rb->count == 0;
}

bool rb_is_full(const ring_buffer_t *rb)
{
    return rb->count == rb->size;
}
