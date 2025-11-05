#Pengine/Pengine.cmake

get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

message("[${TARGET_NAME}] Starting source file fetching in [${CMAKE_CURRENT_SOURCE_DIR}]")

include(FetchContent)

#PenMath
FetchContent_Declare(
	PenMath
	GIT_REPOSITORY  https://github.com/PeanutsPenguin/PenMath
	GIT_TAG main
)
FetchContent_MakeAvailable(PenMath)

### ------- Header files

file(GLOB_RECURSE TARGET_HEADER_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.h
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.inl
	${CMAKE_CURRENT_SOURCE_DIR}/*.natvis
	${CMAKE_CURRENT_SOURCE_DIR}/.editorconfig
        ${CMAKE_CURRENT_SOURCE_DIR}/*.sln.DotSettings)
list(FILTER TARGET_HEADER_FILES EXCLUDE REGEX ${CMAKE_CURRENT_BINARY_DIR})

### ------- Source (C++) files

file(GLOB_RECURSE TARGET_SOURCE_FILES 
	${CMAKE_CURRENT_SOURCE_DIR}/*.cd
	${CMAKE_CURRENT_SOURCE_DIR}/*.c
	${CMAKE_CURRENT_SOURCE_DIR}/*.cc
	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/*.cxx
	${CMAKE_CURRENT_SOURCE_DIR}/*.c++)
list(FILTER TARGET_SOURCE_FILES EXCLUDE REGEX ${CMAKE_CURRENT_BINARY_DIR})



### ------- DLL files 
file(GLOB_RECURSE TARGET_DLL_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/DLL/*.dll)
set(BIN_DEPENDENCIES ${TARGET_DLL_FILES} PARENT_SCOPE)

### ------- .lib files 
file(GLOB_RECURSE TARGET_LIB_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*/Addon/*.lib)
file(GLOB_RECURSE TARGET_DEBUG_LIB_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*/Debug/*.lib)
file(GLOB_RECURSE TARGET_RELEASE_LIB_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*/Release/*.lib)
list(FILTER TARGET_EXTRA_FILES EXCLUDE REGEX ${CMAKE_CURRENT_BINARY_DIR})

### ------- Set "Debug" .lib files
foreach(LIB ${TARGET_DEBUG_LIB_FILES})
	set(TARGET_LIB_FILES ${TARGET_LIB_FILES} debug ${LIB})
endforeach()

### ------- Set "Release" .lib files
foreach(LIB ${TARGET_RELEASE_LIB_FILES})
	set(TARGET_LIB_FILES ${TARGET_LIB_FILES} optimized ${LIB})
endforeach()

set(TARGET_FILES ${TARGET_HEADER_FILES} ${TARGET_SOURCE_FILES})

add_library(
  ${TARGET_NAME}
  STATIC
)

# ------- Create Penditor/Assets directory if it doesn't exist
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory "${PROJECT_SOURCE_DIR}/Penditor/Assets"
  VERBATIM
)

# ------- copy each discovered DLL into Penditor/Assets
foreach(_dll ${TARGET_DLL_FILES})
  get_filename_component(_dll_name "${_dll}" NAME)
  add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${_dll}" "${PROJECT_SOURCE_DIR}/Penditor/Assets/${_dll_name}"
    VERBATIM
  )
endforeach()


target_sources(${TARGET_NAME} PRIVATE ${TARGET_FILES})

target_link_libraries(${TARGET_NAME} PRIVATE ${TARGET_LIB_FILES})
target_link_libraries(${TARGET_NAME} PUBLIC PenMath)

target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Header)
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/Header)

foreach(DIRECTORY ${TARGET_DIRECTORIES})
    if(IS_DIRECTORY ${DIRECTORY})
	target_include_directories(${TARGET_NAME} PRIVATE ${DIRECTORY})
    else() 
	continue() 
    endif()
endforeach()

### ------- Tells MSVC to parallel build for faster compilation and allow the compiler to create object files with more than 65,536 sections

if (MSVC)
    add_definitions(/MP)
    target_compile_options(${TARGET_NAME} PRIVATE /bigobj)
endif()

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TARGET_FILES})

### ------- Append all target files in one group

function(add_source_group_dir path)
  set(headerDir "${CMAKE_CURRENT_SOURCE_DIR}/Header/${path}")
  set(sourceDir "${CMAKE_CURRENT_SOURCE_DIR}/Source/${path}")
  file(GLOB headerFiles LIST_DIRECTORIES false "${headerDir}/*")
  file(GLOB sourceFiles LIST_DIRETORIES false "${sourceDir}/*")

  source_group("${path}/Header" FILES ${headerFiles})
  source_group("${path}/Source" FILES ${sourceFiles})

  file(GLOB children RELATIVE "${headerDir}" "${headerDir}/*")
  foreach(child ${children})
    if(IS_DIRECTORY "${headerDir}/${child}")
      add_source_group_dir("${path}/${child}")
    endif()
  endforeach()
endfunction()

file(GLOB children RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}/Header" "${CMAKE_CURRENT_SOURCE_DIR}/Header/*")
foreach(child ${children})
  if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Header/${child}")
    add_source_group_dir("${child}")
  endif()
endforeach()


set(MODERN_LIBRARY ${TARGET_NAME} PARENT_SCOPE)

message("[${TARGET_NAME}] Done.")
