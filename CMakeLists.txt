cmake_minimum_required(VERSION 3.10.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_HOME_DIRECTORY}/build")
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_HOME_DIRECTORY}/build")
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_HOME_DIRECTORY}/build")

project(PO_GO)


if(MSVC)
    #static library
    add_compile_options(/W3 /O2 /MT)
endif()

set(BUILD_SHARED_LIBS FALSE)
set(SFML_USE_STATIC_STD_LIBS TRUE)
add_subdirectory(SFML)
	
include_directories("include" ${SFML_INCLUDE_DIR})
file(GLOB SOURCES "src/*.cpp")
file(GLOB HEADERS "include/*.h")


add_executable(PO_GO ${SOURCES} ${HEADERS})
target_compile_definitions(PO_GO PRIVATE SFML_STATIC)
target_link_libraries(PO_GO sfml-graphics sfml-window sfml-system)