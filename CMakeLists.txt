#Root CMAKE
cmake_minimum_required (VERSION 4.1.1 FATAL_ERROR)

set (CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_STANDARD_REQUIRED True)

get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJECT_NAME} LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(Pengine)
add_subdirectory(Penditor)

if (MSVC)
	set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Penditor)
endif()
