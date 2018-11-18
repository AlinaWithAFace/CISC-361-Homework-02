cmake_minimum_required(VERSION 3.12)
project(HW_Threads_RealSemaphores C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(HW_Threads_RealSemaphores
        barrier.c
        common_threads.h
        fork-join.c
        mutex-nostarve.c
        reader-writer-nostarve.c
        reader-writer.c
        rendezvous.c)
