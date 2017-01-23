cmake_minimum_required (VERSION 2.8 FATAL_ERROR)

set(CMAKE_C_COMPILER "/usr/bin/gcc-6")
set(CMAKE_CXX_COMPILER "/usr/bin/g++-6")

project (elektron)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pthread -lrt")
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DELEKTRON_DEBUG")

set (SOURCES
	communicationbuffer.cpp
	timer.cpp
)

set (HEADERS
	communicationbuffer.h
	timer.h
	)

target_link_libraries(lrt)
add_executable(elektron elektron4.cpp ${SOURCES})
