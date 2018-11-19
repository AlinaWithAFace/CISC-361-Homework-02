cmake_minimum_required(VERSION 3.12)
project(HW_Threads_RealSemaphores C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(fork-join
        fork-join.c)

add_executable(rendezvous
        rendezvous.c)

add_executable(barrier
        barrier.c)

add_executable(reader-writer
        reader-writer.c
        common_threads.h)