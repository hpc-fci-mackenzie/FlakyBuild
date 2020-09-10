cmake_minimum_required(VERSION "3.15")

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -DDEBUG")

project(nsa)

set(CMAKE_CXX_STANDARD 11)

set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_executable(nsa nsa.cpp)

target_link_libraries (nsa ${CMAKE_THREAD_LIBS_INIT})
