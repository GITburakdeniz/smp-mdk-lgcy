set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(smp 
	${SMP2_SOURCES}
)

target_include_directories(smp PRIVATE
	${CMAKE_CURRENT_LIST_DIR}	
)

install(TARGETS smp DESTINATION lib)

install(DIRECTORY Smp
        DESTINATION include        
)

install(DIRECTORY Smp
        DESTINATION include 
        FILES_MATCHING 
        PATTERN "Mdk/*.h" 
)