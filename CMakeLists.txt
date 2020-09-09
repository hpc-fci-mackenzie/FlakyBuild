cmake_minimum_required(VERSION "3.15")

project(nsa)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGSDEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGSDEBUG_INIT "-DDEBUG")

set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

add_executable(nsa nsa.cpp)

target_link_libraries (nsa ${CMAKE_THREAD_LIBS_INIT})
