cmake_minimum_required(VERSION 3.18)

project(rolgame)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

include(CTest)
include(GNUInstallDirs)
include(CMakeOptions.txt)
include_directories(lib)

if(${COVERAGE})
	include(CodeCoverage)
endif(${COVERAGE})

add_subdirectory(lib)
if(${TESTS})
add_subdirectory(tests)
	if(${COVERAGE})
		coverage_target(. */lib/* check)
	endif(${COVERAGE})
endif(${TESTS})
add_subdirectory(bin)

message(STATUS "TESTS " ${TESTS})
message(STATUS "COVERAGE " ${COVERAGE})
