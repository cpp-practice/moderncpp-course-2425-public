cmake_minimum_required(VERSION 3.16)
project(cpp2122_semester2)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -O3")
# or -fcoroutines-ts

add_executable(01_exec_with_interruptions 01_exec_with_interruptions.cpp)
add_executable(02_generator 02_generator.cpp)

add_executable(my_first_coroutine my_first_coroutine.cpp)

add_executable(co_await_1 co_await_1.cpp)
add_executable(co_await_2 co_await_2.cpp)
add_executable(co_await_3 co_await_3.cpp)
