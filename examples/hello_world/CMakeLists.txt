cmake_minimum_required(VERSION 3.10)

# set the project name
project(hello-smp)

# add the executable
add_executable(hello-smp main.cpp ${SMP2_SOURCES})

include_directories(hello-smp "../../src/" )