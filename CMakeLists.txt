project(ExampleProject)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_FRAMEWORK_DIR ${CMAKE_SOURCE_DIR}/cmake/framework)

if(NOT EXISTS ${CMAKE_FRAMEWORK_DIR})
execute_process(
		#COMMAND git clone ${PROJECT_SOURCE_DIR}/.. ${CMAKE_FRAMEWORK_DIR}
		COMMAND git clone https://github.com/dtorban/cmake_fw.git ${CMAKE_FRAMEWORK_DIR}
)
endif()

include(${CMAKE_FRAMEWORK_DIR}/project/MainProject.cmake)

add_subdirectory(src/sandbox)
add_subdirectory(src/sandbox_geometry)
add_subdirectory(src/sandbox_graphics)
add_subdirectory(src/sandbox_threading)
add_subdirectory(plugins)
add_subdirectory(examples)

