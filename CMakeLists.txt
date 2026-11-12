cmake_minimum_required(VERSION 3.14)
project(c_ring_buffer C)

set(CMAKE_C_STANDARD 99)

include(FetchContent)
FetchContent_Declare(
    unity
    GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity.git
    GIT_TAG v2.6.0
)
FetchContent_MakeAvailable(unity)

add_library(ring_buffer src/ring_buffer.c)
target_include_directories(ring_buffer PUBLIC include)
target_compile_options(ring_buffer PRIVATE -Wall -Wextra -Werror)

enable_testing()
add_executable(test_ring_buffer test/test_ring_buffer.c)
target_link_libraries(test_ring_buffer ring_buffer unity)
add_test(NAME ring_buffer_tests COMMAND test_ring_buffer)
