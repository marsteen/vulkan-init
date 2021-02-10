cmake_minimum_required(VERSION 3.10)
project("vktriangle")

message("System: ${CMAKE_SYSTEM_NAME}")



#SET(VULKAN_SDK_WINDOWS "/opt/VulkanSDK/1.2.148.1")
SET(VULKAN_SDK_WINDOWS "/c/VulkanSDK/1.2.162.1")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++17")



#
# GLFW
#
find_package(glfw3 REQUIRED)
if (GLFW3_FOUND)
    message("found GLFW3")
    include_directories($(GLFW3_INCLUDE_DIRS))    
endif()

include_directories(./source)
if (CMAKE_SYSTEM_NAME STREQUAL "MSYS")
    include_directories(./source ${VULKAN_SDK_WINDOWS}/include)
    link_directories(${VULKAN_SDK_WINDOWS}/Lib)
endif()

add_executable(vktriangle
    ../source/main.cpp
    ../source/CVulkanApp.cpp    
)


if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    #
    # Windows
    #
    SET(SYSTEM_NAME "windows")    
    target_link_libraries(vktriangle
        vulkan
        glfw)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    #
    # Linux
    #
    SET(SYSTEM_NAME "linux")
    set_target_properties(vktriangle PROPERTIES OUTPUT_NAME ../bin/linux/vktriangle)
    target_link_libraries(vktriangle
        vulkan
        glfw)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    #
    # Mac OS
    #
    # *TODO*
    SET(SYSTEM_NAME "mac")
endif()


set_target_properties(vktriangle PROPERTIES OUTPUT_NAME ../bin/${SYSTEM_NAME}/vktriangle)    