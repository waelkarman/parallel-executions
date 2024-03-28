cmake_minimum_required(VERSION 3.5)

project(parallel_executions LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_library(timer SHARED timer.hpp)
add_library(ts_vector SHARED ts_vector.hpp)

set_target_properties(timer PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(ts_vector PROPERTIES LINKER_LANGUAGE CXX)

add_executable(sync_threads_one
    sync_threads_one.cpp
)

add_executable(sync_schedule_threads
    sync_schedule_threads.cpp
)

add_executable(scalable_task_processing
    scalable_task_processing.cpp
    task_scaler.h task_scaler.cpp
)

add_executable(sync_threads_all
    sync_threads_all.cpp
)

target_include_directories(timer PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

include(GNUInstallDirs)

install(TARGETS sync_threads_all
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(TARGETS sync_threads_one
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(TARGETS sync_schedule_threads
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(TARGETS scalable_task_processing
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
