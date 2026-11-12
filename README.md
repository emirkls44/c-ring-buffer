# C Ring Buffer

![CI](https://github.com/emirkls44/c-ring-buffer/actions/workflows/ci.yml/badge.svg)

A small ring buffer (circular buffer) library in C, the kind used to queue UART bytes on a microcontroller. It uses no dynamic memory: the caller passes in the storage array.

The library is tested with Unity and the tests run automatically on every push with GitHub Actions.

## Build and test

```
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Usage

```c
uint8_t storage[64];
ring_buffer_t rb;
rb_init(&rb, storage, sizeof(storage));

rb_put(&rb, 0x42);

uint8_t byte;
rb_get(&rb, &byte);
```
