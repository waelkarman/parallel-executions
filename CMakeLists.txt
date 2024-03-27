cmake_minimum_required(VERSION 3.5)

project(parallel_executions LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

set(HEADERS
    timer.hpp
)

add_library(timer SHARED ${HEADERS})

set_target_properties(timer PROPERTIES LINKER_LANGUAGE CXX)

add_executable(sync_vector
    sync_vector.cpp
)

add_executable(sync_sequential_execution
    sync_sequential_execution.cpp
)

add_executable(sync_schedule_thread
    sync_schedule_thread.cpp
)

add_executable(synch_threads
    sync_threads.cpp
)

target_include_directories(timer PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

include(GNUInstallDirs)
install(TARGETS sync_vector
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(TARGETS synch_threads
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(TARGETS sync_sequential_execution
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(TARGETS sync_schedule_thread
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
