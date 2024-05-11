cmake_minimum_required(VERSION 3.5)

project(parallel_executions LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_library(timer SHARED ./lib/timer.hpp)
add_library(ts_vector SHARED ./drafts/ts_vector.hpp)

set_target_properties(timer PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(ts_vector PROPERTIES LINKER_LANGUAGE CXX)

add_executable(sync_threads_all
    ./drafts/sync_threads_all.cpp
)

add_executable(sync_threads_one
    ./drafts/sync_threads_one.cpp
)

add_executable(posix_singlecore_scheduler
    ./POSIX/POSIX_singlecore_scheduler.cpp
)

add_executable(thread_pool
    ./CPP/thread_pool.cpp
)

add_executable(producer_consumer
    ./CPP/producer_consumer.cpp
)

target_include_directories(posix_singlecore_scheduler PUBLIC
    lib
)

target_link_libraries(posix_singlecore_scheduler PUBLIC
    timer
)