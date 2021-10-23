cmake_minimum_required(VERSION 3.10)

# set the project name
project(smp-mdk)

# FIXME 
set( SMP2_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/src/Mdk/Management/EntryPointPublisher.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/Mdk/Management/EventConsumer.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/Mdk/Management/EventProvider.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/Mdk/Management/ManagedComponent.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/Mdk/Management/ManagedObject.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Mdk/Aggregate.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Mdk/AnySimple.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Mdk/Component.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Mdk/Composite.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Mdk/DateTime.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Mdk/Duration.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Mdk/Model.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Mdk/Object.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Mdk/Uuid.cpp

	${CMAKE_CURRENT_LIST_DIR}/src/Smp/Services/Service.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/Smp/Services/Logger.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Smp/Services/Scheduler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Smp/Services/TimeKeeper.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Smp/Services/EventManager.cpp    
	${CMAKE_CURRENT_LIST_DIR}/src/Smp/Simulator.cpp
)

add_subdirectory(src)
add_subdirectory(examples)
#add_subdirectory(tests)