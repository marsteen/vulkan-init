cmake_minimum_required(VERSION 3.10)
project("vktriangle")

message("System: ${CMAKE_SYSTEM_NAME}")

include_directories(./source)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++17")

#
# GLFW
#
find_package(glfw3 REQUIRED)
if (GLFW3_FOUND)
    message("found GLFW3")
    include_directories($(GLFW3_INCLUDE_DIRS))    
endif()



add_executable(vktriangle
    ../source/main.cpp
    ../source/CVulkanApp.cpp    
)

set_target_properties(vktriangle PROPERTIES OUTPUT_NAME ../bin/linux/vktriangle)

if (CMAKE_SYSTEM_NAME STREQUAL "MSYS")
    #
    # Windows
    #
    target_link_libraries(vktriangle
        glfw)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    #
    # Linux
    #
    target_link_libraries(vktriangle
        vulkan
        glfw)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    #
    # Mac OS
    #
    # *TODO*
endif()


