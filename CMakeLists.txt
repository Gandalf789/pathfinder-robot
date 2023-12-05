cmake_minimum_required(VERSION 3.0)

get_filename_component(MyWebotsController ${CMAKE_SOURCE_DIR} NAME)
project(${MyWebotsController})

file(GLOB C_SOURCES *.c)
set(SOURCES ${C_SOURCES})

set(WEBOTS_HOME "/usr/local/webots")

# Compiler flags if needed
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

# Linking directories and libraries from Webots
link_directories(${WEBOTS_HOME}/lib/controller)
set (LIBRARIES m ${CMAKE_SHARED_LIBRARY_PREFIX}Controller${CMAKE_SHARED_LIBRARY_SUFFIX} ${CMAKE_SHARED_LIBRARY_PREFIX}CppController${CMAKE_SHARED_LIBRARY_SUFFIX})
include_directories(/usr/local/webots/include/controller/c/webots)

# Collect source file
#set(SOURCES "/home/timo/Documents/Robot1/controllers/Comenzi/main.c"
#       module1.c
#        module1.h)

# Specify the target executable
add_executable(${MyWebotsController} ${SOURCES})
target_link_libraries(${MyWebotsController} ${LIBRARIES})

# Link necessary libraries with the target
add_custom_command(TARGET ${MyWebotsController} POST_BUILD COMMAND ${CMAKE_COMMAND} -E
        copy ${CMAKE_BINARY_DIR}/${MyWebotsController} ${CMAKE_SOURCE_DIR}
)
