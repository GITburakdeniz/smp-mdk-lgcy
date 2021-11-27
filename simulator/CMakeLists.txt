cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost COMPONENTS system filesystem thread program_options REQUIRED)

# set the project name
project(simulator)

# add the executable
add_executable(${PROJECT_NAME}
    main.cpp 
    ${LIBSMP2_SOURCES}
)

target_link_libraries(${PROJECT_NAME} 
    Boost::filesystem    
    Boost::program_options
    Boost::system
    Boost::thread
    zmq
    pthread
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ../libsmp2/
        ../thirdparty/
        thirdparty
)