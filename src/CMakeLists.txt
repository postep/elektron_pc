cmake_minimum_required (VERSION 2.8 FATAL_ERROR)

set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

project (elektron)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pthread")
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DELEKTRON_DEBUG")

set (SOURCES
	communicationbuffer.cpp
	timer.cpp
	yahdlc/C/fcs16.c
	yahdlc/C/yahdlc.c
)

set (HEADERS
	communicationbuffer.h
	timer.h
	yahdlc/C/fcs16.h
	yahdlc/C/yahdlc.h 
	)

add_executable(elektron elektron4.cpp ${SOURCES})
