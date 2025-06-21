cmake_minimum_required(VERSION 3.10)
project("vktriangle")

message("System: ${CMAKE_SYSTEM_NAME}")

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    SET(SYSTEM_NAME "windows")    
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    SET(SYSTEM_NAME "linux")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    SET(SYSTEM_NAME "mac")
endif()

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

#
# GLM
#
find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIR})

#
# Vulkan SDK
#
find_package(Vulkan REQUIRED)
if (Vulkan_FOUND)
	include_directories(${Vulkan_INCLUDE_DIRS})
endif()

#
# Shaders
#
function(add_shader SHADER)
    message("found shader:" ${SHADER})
	get_filename_component(fileNoExt ${SHADER} NAME_WE)
	set(shader-src-file ${CMAKE_CURRENT_SOURCE_DIR}/shaders/${SHADER})
	set(shader-dst-file ${CMAKE_CURRENT_SOURCE_DIR}/bin/${SYSTEM_NAME}/shaders/${fileNoExt}.spv)
	get_filename_component(shader-output-dir ${shader-dst-file} DIRECTORY)
	file(MAKE_DIRECTORY ${shader-output-dir})

	add_custom_command(
			TARGET  ${CMAKE_PROJECT_NAME}
            POST_BUILD
			COMMAND glslc -o ${shader-dst-file} ${shader-src-file}
			VERBATIM)
endfunction(add_shader)

file(GLOB vertex-shaders ${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.vert)
file(GLOB fragment-shaders ${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.frag)

#
#
#


if (CMAKE_SYSTEM_NAME STREQUAL "MSYS")
    include_directories(./source ${VULKAN_SDK_WINDOWS}/include)
    link_directories(${VULKAN_SDK_WINDOWS}/Lib)
endif()

include_directories(./source)

add_executable(${CMAKE_PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/CVulkanApp.cpp    
)

foreach(vertex-shader ${vertex-shaders})
	get_filename_component(p ${vertex-shader} NAME)
	add_shader(${p})
endforeach(vertex-shader)

foreach(fragment-shader ${fragment-shaders})
	get_filename_component(p ${fragment-shader} NAME)
	add_shader(${p})
endforeach(fragment-shader)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(vktriangle
        vulkan
        glfw)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_link_libraries(vktriangle
        ${Vulkan_LIBRARIES}
        glfw)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    #
    # Mac OS
    #
    # *TODO*
endif()


set_target_properties(vktriangle PROPERTIES OUTPUT_NAME ../bin/${SYSTEM_NAME}/vktriangle)    
