#include "unity.h"
#include "ring_buffer.h"

#define SIZE 4

static uint8_t storage[SIZE];
static ring_buffer_t rb;

void setUp(void)
{
    rb_init(&rb, storage, SIZE);
}

void tearDown(void)
{
}

void test_new_buffer_is_empty(void)
{
    TEST_ASSERT_TRUE(rb_is_empty(&rb));
    TEST_ASSERT_FALSE(rb_is_full(&rb));
    TEST_ASSERT_EQUAL_UINT32(0, rb_count(&rb));
}

void test_get_from_empty_returns_false(void)
{
    uint8_t byte;
    TEST_ASSERT_FALSE(rb_get(&rb, &byte));
}

void test_put_then_get_returns_same_byte(void)
{
    uint8_t byte = 0;
    TEST_ASSERT_TRUE(rb_put(&rb, 0x42));
    TEST_ASSERT_TRUE(rb_get(&rb, &byte));
    TEST_ASSERT_EQUAL_HEX8(0x42, byte);
}

void test_bytes_come_out_in_fifo_order(void)
{
    uint8_t byte;
    rb_put(&rb, 1);
    rb_put(&rb, 2);
    rb_put(&rb, 3);

    rb_get(&rb, &byte);
    TEST_ASSERT_EQUAL_UINT8(1, byte);
    rb_get(&rb, &byte);
    TEST_ASSERT_EQUAL_UINT8(2, byte);
    rb_get(&rb, &byte);
    TEST_ASSERT_EQUAL_UINT8(3, byte);
}

void test_put_to_full_buffer_returns_false(void)
{
    for (int i = 0; i < SIZE; i++) {
        TEST_ASSERT_TRUE(rb_put(&rb, (uint8_t)i));
    }
    TEST_ASSERT_TRUE(rb_is_full(&rb));
    TEST_ASSERT_FALSE(rb_put(&rb, 99));
}

void test_full_buffer_keeps_old_data(void)
{
    uint8_t byte;
    for (int i = 0; i < SIZE; i++) {
        rb_put(&rb, (uint8_t)(10 + i));
    }
    rb_put(&rb, 99);

    rb_get(&rb, &byte);
    TEST_ASSERT_EQUAL_UINT8(10, byte);
}

void test_indexes_wrap_around(void)
{
    uint8_t byte;
    for (int round = 0; round < 3 * SIZE; round++) {
        TEST_ASSERT_TRUE(rb_put(&rb, (uint8_t)round));
        TEST_ASSERT_TRUE(rb_get(&rb, &byte));
        TEST_ASSERT_EQUAL_UINT8(round, byte);
    }
    TEST_ASSERT_TRUE(rb_is_empty(&rb));
}

void test_count_follows_put_and_get(void)
{
    uint8_t byte;
    rb_put(&rb, 1);
    rb_put(&rb, 2);
    TEST_ASSERT_EQUAL_UINT32(2, rb_count(&rb));
    rb_get(&rb, &byte);
    TEST_ASSERT_EQUAL_UINT32(1, rb_count(&rb));
}

void test_reset_empties_buffer(void)
{
    rb_put(&rb, 1);
    rb_put(&rb, 2);
    rb_reset(&rb);
    TEST_ASSERT_TRUE(rb_is_empty(&rb));
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_new_buffer_is_empty);
    RUN_TEST(test_get_from_empty_returns_false);
    RUN_TEST(test_put_then_get_returns_same_byte);
    RUN_TEST(test_bytes_come_out_in_fifo_order);
    RUN_TEST(test_put_to_full_buffer_returns_false);
    RUN_TEST(test_full_buffer_keeps_old_data);
    RUN_TEST(test_indexes_wrap_around);
    RUN_TEST(test_count_follows_put_and_get);
    RUN_TEST(test_reset_empties_buffer);
    return UNITY_END();
}
