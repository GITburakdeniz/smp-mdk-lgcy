cmake_minimum_required(VERSION 3.10)

find_package(Boost COMPONENTS system filesystem REQUIRED)

# set the project name
project(hello-smp)

# add the executable
add_executable(hello-smp main.cpp ${SMP2_SOURCES})

target_link_libraries(hello-smp 
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    pthread
)

include_directories(hello-smp "../../src/" )